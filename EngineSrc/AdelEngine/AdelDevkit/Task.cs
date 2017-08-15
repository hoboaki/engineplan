using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Adel.Adk
{
    public class TaskCommandArg
    {
        public TaskCommandArg(Logger aLogger)
        {
            _Logger = aLogger;
        }

        public Logger Logger { get; }
        Logger _Logger;
    }

    public class TaskCommand
    {
        public TaskCommand(Action<TaskCommandArg> aAction)
        {
            _Action = aAction;
        }

        public void Exec(TaskCommandArg aArg)
        {
            _Action(aArg);
        }

        Action<TaskCommandArg> _Action;
    }


    public class Task
    {
        public Task(TaskCommand aCommand)
        {
            _Commands = new List<TaskCommand> { aCommand }.ToArray();
        }

        public Task(IEnumerable<TaskCommand> aCommands)
        {
            _Commands = aCommands.ToArray();
        }

        TaskCommand[] _Commands;
    }
}
