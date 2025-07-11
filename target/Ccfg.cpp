/******************************************************************************
 *  Copyright (c) 2022-2024 Texas Instruments Incorporated
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions are met:
 *
 *  1) Redistributions of source code must retain the above copyright notice,
 *     this list of conditions and the following disclaimer.
 *
 *  2) Redistributions in binary form must reproduce the above copyright notice,
 *     this list of conditions and the following disclaimer in the documentation
 *     and/or other materials provided with the distribution.
 *
 *  3) Neither the name of the copyright holder nor the names of its
 *     contributors may be used to endorse or promote products derived from this
 *     software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 *  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 *  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 *  ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 *  LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 *  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 *  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 *  INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 *  CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 *  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 *  POSSIBILITY OF SUCH DAMAGE.
 *
 ******************************************************************************/

 #ifndef __CCFC_C__
 #define __CCFC_C__
 
 #include "ti/devices/cc23x0r5/inc/hw_ccfg.h"
 
 extern void (*const resetVectors[])(void);
 
 /*! \brief Default ccfg struct definition
  *  Defines the ccfg structure and field configuration with default values.
  *  If fields are to be overridden, the structure below should be modified in
  *  place or copied into a new C file to avoid contaminating the local SDK
  *  installation.
  */
 #if defined(__IAR_SYSTEMS_ICC__)
 __root const ccfg_t ccfg @ ".ccfg" =
 #elif defined(__llvm__)
 #pragma GCC diagnostic ignored "-Woverride-init"
 #pragma GCC diagnostic ignored "-Wmissing-braces"
 const ccfg_t ccfg __attribute__((section(".ccfg"), retain)) =
 #elif (defined(__GNUC__))
 #pragma GCC diagnostic ignored "-Woverride-init"
 #pragma GCC diagnostic ignored "-Wmissing-braces"
 const ccfg_t ccfg __attribute__((section(".ccfg"), used)) =
 #else
 #error "Unsupported compiler used. Expected one of [TI Clang, IAR, GCC]"
 #endif
     {
         CCFG_DEFAULT_VALUES,
         // Manual overrides
 
         .bootCfg.bldrParam.serialRomBldrParamStruct.bldrEnabled = XCFG_BC_BLDR_DIS,
         .bootCfg.bldrParam.serialRomBldrParamStruct.serialIoCfgIndex = 0,
         .bootCfg.bldrParam.serialRomBldrParamStruct.pinTriggerDio = 0,
         .bootCfg.bldrParam.serialRomBldrParamStruct.pinTriggerEnabled = XCFG_BC_PINTRIG_DIS,
         .bootCfg.bldrParam.serialRomBldrParamStruct.pinTriggerLevel = XCFG_BC_PINTRIG_LEVEL_LO,
         .bootCfg.pAppVtor = (void*)&resetVectors,
 
         /* Set to 0. This checksum must be calculated and updated prior to
          * programming the application to the device (this is normally handled as a
          * post-build step, or by the flashloader).
          */
         .bootCfg.crc32 = 0x00000000,
 
         .hwOpts = { 0xFFFFFFFF, 0xFFFFFFFF },
 
         .permissions.allowDebugPort = CCFG_PERMISSION_ALLOW,
         .permissions.allowEnergyTrace = CCFG_PERMISSION_ALLOW,
         .permissions.allowFlashVerify = CCFG_PERMISSION_ALLOW,
         .permissions.allowFlashProgram = CCFG_PERMISSION_ALLOW,
         .permissions.allowChipErase = CCFG_PERMISSION_ALLOW,
         .permissions.allowToolsClientMode = CCFG_PERMISSION_ALLOW,
         .permissions.allowFakeStby = CCFG_PERMISSION_ALLOW,
         .permissions.allowReturnToFactory = CCFG_PERMISSION_ALLOW,
 
         .misc.saciTimeoutOverride = 0U,
 
         .flashProt.writeEraseProt.mainSectors0_31 = 0xffffffff,
         .flashProt.writeEraseProt.mainSectors32_255 = 0xffffffff,
 
         .flashProt.writeEraseProt.ccfgSector = 0,
         .flashProt.writeEraseProt.fcfgSector = 0,
         .flashProt.writeEraseProt.engrSector = 0,
 
         .flashProt.res = 0xFFFFFFFFU,
 
         .flashProt.chipEraseRetain.mainSectors0_31 = 0x0,
         /* The four most significant bits of erase and retain main sectors must be set to one.
          * Otherwise, the SACI command to erase and retain main sectors will fail.
          */
         .flashProt.chipEraseRetain.mainSectors32_255 = (0x0 | 0xF0000000),
 
         /* Set to 0. This checksum (across hwOpts through hwInitCopyList) must be
          * calculated and updated prior to programming the application to the device
          * (this is normally handled as a post-build step, or by the flashloader).
          */
         .crc32 = 0x00000000,
 
         /* No user record */
 
         .debugCfg.authorization = CCFG_DBGAUTH_DBGOPEN,
         .debugCfg.allowBldr = CCFG_DBGBLDR_ALLOW,
         .debugCfg.pwdId = { 0x01, 0x01, 0x02, 0x03, 0x05, 0x08, 0x0d, 0x15 },
         .debugCfg.pwdHash = { 0x6d, 0xd7, 0xe4, 0x36, 0xeb, 0xf4, 0x31, 0xdf,
             0x95, 0xae, 0x15, 0xee, 0x03, 0xba, 0x8e, 0xe4,
             0xc4, 0xc6, 0x3f, 0xd8, 0x45, 0x3f, 0x67, 0x5e,
             0x74, 0xd7, 0xc2, 0x01, 0x2c, 0x90, 0x58, 0xe5 },
 
         /* Set to 0. This checksum must be calculated and updated prior to
          * programming the application to the device (this is normally handled as a
          * post-build step, or by the flashloader).
          */
         .debugCfg.crc32 = 0x00000000,
     };
 
 #endif // __CCFC_C__
 