using System;

namespace Names
{
  internal static class HeatmapTask
  {
    public static HeatmapData GetHistogramBirthsPerDate(NameData[] names)
    {
      var minDay = 2;
      var numberOfDays = 31;
      var daysNumbers = new string[numberOfDays - 1];
      for (int i = 0; i < numberOfDays - 1; i++)
          daysNumbers[i] = (i + minDay).ToString();

      var numberOfMonths = 12;
      var monthsNumbers = new string[numberOfMonths];
      for (int i = 0; i < numberOfMonths; i++)
          monthsNumbers[i] = (i + 1).ToString();

      var birthsCounts = new double[numberOfDays - 1, numberOfMonths];
      foreach (var person in names)
      {
          if (person.BirthDate.Day != 1)
              birthsCounts[person.BirthDate.Day - minDay, person.BirthDate.Month - 1]++;
      }

      return new HeatmapData("Пример карты интенсивностей", birthsCounts, daysNumbers, monthsNumbers);
    }
  }
}
