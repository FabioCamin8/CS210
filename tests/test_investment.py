"""Regression checks for the two Airgead Banking investment reports."""

import re
import subprocess
import tempfile
import unittest
from pathlib import Path


PROJECT_ROOT = Path(__file__).resolve().parents[1]
ROW = re.compile(r"^\s*(\d+)\s+\$([\d,.]+)\s+\$([\d,.]+)\s*$")


class InvestmentReportTests(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.build_dir = tempfile.TemporaryDirectory()
        cls.executable = Path(cls.build_dir.name) / "airgead-banking"
        subprocess.run(
            ["g++", "-std=c++11", "-Wall", "-Wextra", "-pedantic",
             str(PROJECT_ROOT / "main.cpp"),
             str(PROJECT_ROOT / "AirgeadBanking.cpp"),
             "-o", str(cls.executable)],
            check=True,
        )

    @classmethod
    def tearDownClass(cls):
        cls.build_dir.cleanup()

    def run_calculator(self, inputs):
        result = subprocess.run(
            [str(self.executable)], input=inputs, text=True,
            capture_output=True, check=True, timeout=10,
        )
        output = result.stdout
        before, after = output.split(
            "Balance and Interest With Additional Monthly Deposits", maxsplit=1
        )

        def rows(section):
            return [
                (int(match.group(1)), float(match.group(2).replace(",", "")),
                 float(match.group(3).replace(",", "")))
                for line in section.splitlines()
                if (match := ROW.match(line))
            ]

        return rows(before), rows(after), output

    def test_no_deposits_use_annual_compounding(self):
        no_deposits, _, _ = self.run_calculator("1000\n100\n12\n2\n\nn\n")
        self.assertEqual(no_deposits, [(1, 1120.00, 120.00),
                                       (2, 1254.40, 134.40)])

    def test_monthly_deposits_use_monthly_compounding(self):
        _, with_deposits, _ = self.run_calculator("1000\n100\n12\n2\n\nn\n")
        balance = 1000.0
        expected = []
        for year in range(1, 3):
            interest_earned = 0.0
            for _ in range(12):
                interest = (balance + 100.0) * 0.01
                balance += 100.0 + interest
                interest_earned += interest
            expected.append((year, round(balance, 2), round(interest_earned, 2)))
        self.assertEqual(with_deposits, expected)

    def test_validation_rejects_invalid_numbers(self):
        no_deposits, _, output = self.run_calculator(
            "not a number\n1000\n-10\n100\n0\n12\n2.5\n2\n\nn\n"
        )
        self.assertEqual(output.count("Invalid input."), 4)
        self.assertEqual(no_deposits[0], (1, 1120.00, 120.00))


if __name__ == "__main__":
    unittest.main()
