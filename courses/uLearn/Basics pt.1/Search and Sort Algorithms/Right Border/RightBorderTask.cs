using System;
using System.Collections.Generic;

namespace Autocomplete
{
    public class RightBorderTask
    {
        public static int GetRightBorderIndex(IReadOnlyList<string> phrases, string prefix,
											  int left, int right)
        {
            while (right - left > 1)
            {
                var middle = (right - left) / 2 + left;

                if (string.Compare(prefix, phrases[middle], StringComparison.OrdinalIgnoreCase) >= 0
                    || phrases[middle].StartsWith(prefix, StringComparison.OrdinalIgnoreCase))
                {
                    left = middle;
                }
                else
                {
                    right = middle;
                }
            }

            return right;
        }
    }
}
