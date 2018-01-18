using System;
using System.Collections.Generic;

namespace Autocomplete
{
    public class LeftBorderTask
    {
        public static int GetLeftBorderIndex(IReadOnlyList<string> phrases, string prefix, int left, int right)
        {
            if (right - left <= 1)
            {
                return left;
            }

            var middle = (right - left) / 2 + left;

            if (string.Compare(prefix, phrases[middle], StringComparison.OrdinalIgnoreCase) < 0
                || phrases[middle].StartsWith(prefix, StringComparison.OrdinalIgnoreCase))
            {
                return GetLeftBorderIndex(phrases, prefix, left, middle);
            }

            return GetLeftBorderIndex(phrases, prefix, middle, right);   
        }
    }
}
