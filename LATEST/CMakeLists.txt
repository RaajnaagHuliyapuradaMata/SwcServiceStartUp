add_library(
   BswAUTOSAR_Service_StartUp
   StartUp.cpp
)

include_directories(
   ../../common/LATEST
   ../../common/LATEST/Compiler_Abstraction_GNU/LATEST
   ../../SwcServiceEcuM/LATEST
   ../../SwcServiceOs/LATEST
   ../../BswAUTOSAR_Service_EcuM/LATEST
   ../../BswAUTOSAR_Service_SchM/LATEST
)

