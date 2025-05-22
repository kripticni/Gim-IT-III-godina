import sys
from collections import Counter
import string


def frequency_analysis(filepath):
    try:
        with open(filepath, "r", encoding="utf-8") as f:
            text = f.read()
    except Exception as e:
        print(f"Greska pri citanju: {e}")
        return

    filtered = [c.lower() for c in text if c.lower() in string.ascii_lowercase]
    freq = Counter(filtered)

    for letter, count in freq.most_common():
        print(f"{letter}: {count}")


if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("Koriscenje: python freqAnalysis.py <fajl>")
    else:
        frequency_analysis(sys.argv[1])
