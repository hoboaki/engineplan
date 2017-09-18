using AdelDevKit.BuildSystem;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using AdelDevKit;
using AdelDevKit.PluginSystem;
using AdelDevKit.Setting.Platform;
using AdelDevKit.TaskSystem;

namespace AdelBuildKitWin
{
    class VisualStudioBuilder : BuilderAddonBase
    {
        public override void Setup(AddonSetupArg aArg)
        {
        }
        
        public override string Name
        {
            get
            {
                return nameof(AdelBuildKitWin) + "." + nameof(VisualStudioBuilder);
            }
        }

        public override string DefaultCoreOs
        {
            get
            {
                return CoreOsWin.StaticName;
            }
        }

        public override string DefaultCoreGfx
        {
            get
            {
                return CoreGfxGl330.StaticName;
            }
        }

        public override string DefaultCoreSnd
        {
            get
            {
                return CoreSndAl.StaticName;
            }
        }

        public override AdelDevKit.TaskSystem.Task CreateBuildTask(BuildArg aArg)
        {
            throw new NotImplementedException();
        }

        public override CpuBit GetCpuBit(BuilderParamInfo aParam)
        {
            return CpuBit.Bit64;
        }

        public override Endian GetEndian(BuilderParamInfo aParam)
        {
            return Endian.LittleEndian;
        }
    }
}
