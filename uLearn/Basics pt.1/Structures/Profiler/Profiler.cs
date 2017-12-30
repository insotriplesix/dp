using System.Collections.Generic;
using System.Diagnostics;

namespace Profiling
{
	public class ProfilerTask : IProfiler
	{
		public List<ExperimentResult> Measure(IRunner runner, int repetitionsCount)
		{
            var result = new List<ExperimentResult>();
			
            double classTime;
            double structTime;

            foreach (var size in Constants.FieldCounts)
            {
				MakeExperiment(runner, true, size, 1);
                classTime = MakeExperiment(runner, true, size, repetitionsCount);
				
				MakeExperiment(runner, false, size, 1);
                structTime = MakeExperiment(runner, false, size, repetitionsCount);
				
                result.Add(new ExperimentResult(size, classTime, structTime));
            }

            return result;
        }

        public double MakeExperiment(IRunner runner, bool isClass, int size, int count)
        {
            var timer = new Stopwatch();

            timer.Start();
            runner.Call(isClass, size, count);
            timer.Stop();

            return (double)timer.ElapsedMilliseconds / count;
        }
	}
}
