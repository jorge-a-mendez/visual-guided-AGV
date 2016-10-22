################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../Generated_Code/Actualizador_Estados.c" \
"../Generated_Code/Cpu.c" \
"../Generated_Code/IO_Map.c" \
"../Generated_Code/IRRx.c" \
"../Generated_Code/IRRx_Watchdog.c" \
"../Generated_Code/Left_Motor.c" \
"../Generated_Code/Left_Motor_Ref.c" \
"../Generated_Code/Muestreador.c" \
"../Generated_Code/Parada.c" \
"../Generated_Code/Right_Motor.c" \
"../Generated_Code/Right_Motor_Ref.c" \
"../Generated_Code/Sensores.c" \
"../Generated_Code/Vectors.c" \

C_SRCS += \
../Generated_Code/Actualizador_Estados.c \
../Generated_Code/Cpu.c \
../Generated_Code/IO_Map.c \
../Generated_Code/IRRx.c \
../Generated_Code/IRRx_Watchdog.c \
../Generated_Code/Left_Motor.c \
../Generated_Code/Left_Motor_Ref.c \
../Generated_Code/Muestreador.c \
../Generated_Code/Parada.c \
../Generated_Code/Right_Motor.c \
../Generated_Code/Right_Motor_Ref.c \
../Generated_Code/Sensores.c \
../Generated_Code/Vectors.c \

OBJS += \
./Generated_Code/Actualizador_Estados_c.obj \
./Generated_Code/Cpu_c.obj \
./Generated_Code/IO_Map_c.obj \
./Generated_Code/IRRx_c.obj \
./Generated_Code/IRRx_Watchdog_c.obj \
./Generated_Code/Left_Motor_c.obj \
./Generated_Code/Left_Motor_Ref_c.obj \
./Generated_Code/Muestreador_c.obj \
./Generated_Code/Parada_c.obj \
./Generated_Code/Right_Motor_c.obj \
./Generated_Code/Right_Motor_Ref_c.obj \
./Generated_Code/Sensores_c.obj \
./Generated_Code/Vectors_c.obj \

OBJS_QUOTED += \
"./Generated_Code/Actualizador_Estados_c.obj" \
"./Generated_Code/Cpu_c.obj" \
"./Generated_Code/IO_Map_c.obj" \
"./Generated_Code/IRRx_c.obj" \
"./Generated_Code/IRRx_Watchdog_c.obj" \
"./Generated_Code/Left_Motor_c.obj" \
"./Generated_Code/Left_Motor_Ref_c.obj" \
"./Generated_Code/Muestreador_c.obj" \
"./Generated_Code/Parada_c.obj" \
"./Generated_Code/Right_Motor_c.obj" \
"./Generated_Code/Right_Motor_Ref_c.obj" \
"./Generated_Code/Sensores_c.obj" \
"./Generated_Code/Vectors_c.obj" \

C_DEPS += \
./Generated_Code/Actualizador_Estados_c.d \
./Generated_Code/Cpu_c.d \
./Generated_Code/IO_Map_c.d \
./Generated_Code/IRRx_c.d \
./Generated_Code/IRRx_Watchdog_c.d \
./Generated_Code/Left_Motor_c.d \
./Generated_Code/Left_Motor_Ref_c.d \
./Generated_Code/Muestreador_c.d \
./Generated_Code/Parada_c.d \
./Generated_Code/Right_Motor_c.d \
./Generated_Code/Right_Motor_Ref_c.d \
./Generated_Code/Sensores_c.d \
./Generated_Code/Vectors_c.d \

C_DEPS_QUOTED += \
"./Generated_Code/Actualizador_Estados_c.d" \
"./Generated_Code/Cpu_c.d" \
"./Generated_Code/IO_Map_c.d" \
"./Generated_Code/IRRx_c.d" \
"./Generated_Code/IRRx_Watchdog_c.d" \
"./Generated_Code/Left_Motor_c.d" \
"./Generated_Code/Left_Motor_Ref_c.d" \
"./Generated_Code/Muestreador_c.d" \
"./Generated_Code/Parada_c.d" \
"./Generated_Code/Right_Motor_c.d" \
"./Generated_Code/Right_Motor_Ref_c.d" \
"./Generated_Code/Sensores_c.d" \
"./Generated_Code/Vectors_c.d" \

OBJS_OS_FORMAT += \
./Generated_Code/Actualizador_Estados_c.obj \
./Generated_Code/Cpu_c.obj \
./Generated_Code/IO_Map_c.obj \
./Generated_Code/IRRx_c.obj \
./Generated_Code/IRRx_Watchdog_c.obj \
./Generated_Code/Left_Motor_c.obj \
./Generated_Code/Left_Motor_Ref_c.obj \
./Generated_Code/Muestreador_c.obj \
./Generated_Code/Parada_c.obj \
./Generated_Code/Right_Motor_c.obj \
./Generated_Code/Right_Motor_Ref_c.obj \
./Generated_Code/Sensores_c.obj \
./Generated_Code/Vectors_c.obj \


# Each subdirectory must supply rules for building sources it contributes
Generated_Code/Actualizador_Estados_c.obj: ../Generated_Code/Actualizador_Estados.c
	@echo 'Building file: $<'
	@echo 'Executing target #12 $<'
	@echo 'Invoking: HCS08 Compiler'
	"$(HC08ToolsEnv)/chc08" -ArgFile"Generated_Code/Actualizador_Estados.args" -ObjN="Generated_Code/Actualizador_Estados_c.obj" "$<" -Lm="$(@:%.obj=%.d)" -LmCfg=xilmou
	@echo 'Finished building: $<'
	@echo ' '

Generated_Code/%.d: ../Generated_Code/%.c
	@echo 'Regenerating dependency file: $@'
	
	@echo ' '

Generated_Code/Cpu_c.obj: ../Generated_Code/Cpu.c
	@echo 'Building file: $<'
	@echo 'Executing target #13 $<'
	@echo 'Invoking: HCS08 Compiler'
	"$(HC08ToolsEnv)/chc08" -ArgFile"Generated_Code/Cpu.args" -ObjN="Generated_Code/Cpu_c.obj" "$<" -Lm="$(@:%.obj=%.d)" -LmCfg=xilmou
	@echo 'Finished building: $<'
	@echo ' '

Generated_Code/IO_Map_c.obj: ../Generated_Code/IO_Map.c
	@echo 'Building file: $<'
	@echo 'Executing target #14 $<'
	@echo 'Invoking: HCS08 Compiler'
	"$(HC08ToolsEnv)/chc08" -ArgFile"Generated_Code/IO_Map.args" -ObjN="Generated_Code/IO_Map_c.obj" "$<" -Lm="$(@:%.obj=%.d)" -LmCfg=xilmou
	@echo 'Finished building: $<'
	@echo ' '

Generated_Code/IRRx_c.obj: ../Generated_Code/IRRx.c
	@echo 'Building file: $<'
	@echo 'Executing target #15 $<'
	@echo 'Invoking: HCS08 Compiler'
	"$(HC08ToolsEnv)/chc08" -ArgFile"Generated_Code/IRRx.args" -ObjN="Generated_Code/IRRx_c.obj" "$<" -Lm="$(@:%.obj=%.d)" -LmCfg=xilmou
	@echo 'Finished building: $<'
	@echo ' '

Generated_Code/IRRx_Watchdog_c.obj: ../Generated_Code/IRRx_Watchdog.c
	@echo 'Building file: $<'
	@echo 'Executing target #16 $<'
	@echo 'Invoking: HCS08 Compiler'
	"$(HC08ToolsEnv)/chc08" -ArgFile"Generated_Code/IRRx_Watchdog.args" -ObjN="Generated_Code/IRRx_Watchdog_c.obj" "$<" -Lm="$(@:%.obj=%.d)" -LmCfg=xilmou
	@echo 'Finished building: $<'
	@echo ' '

Generated_Code/Left_Motor_c.obj: ../Generated_Code/Left_Motor.c
	@echo 'Building file: $<'
	@echo 'Executing target #17 $<'
	@echo 'Invoking: HCS08 Compiler'
	"$(HC08ToolsEnv)/chc08" -ArgFile"Generated_Code/Left_Motor.args" -ObjN="Generated_Code/Left_Motor_c.obj" "$<" -Lm="$(@:%.obj=%.d)" -LmCfg=xilmou
	@echo 'Finished building: $<'
	@echo ' '

Generated_Code/Left_Motor_Ref_c.obj: ../Generated_Code/Left_Motor_Ref.c
	@echo 'Building file: $<'
	@echo 'Executing target #18 $<'
	@echo 'Invoking: HCS08 Compiler'
	"$(HC08ToolsEnv)/chc08" -ArgFile"Generated_Code/Left_Motor_Ref.args" -ObjN="Generated_Code/Left_Motor_Ref_c.obj" "$<" -Lm="$(@:%.obj=%.d)" -LmCfg=xilmou
	@echo 'Finished building: $<'
	@echo ' '

Generated_Code/Muestreador_c.obj: ../Generated_Code/Muestreador.c
	@echo 'Building file: $<'
	@echo 'Executing target #19 $<'
	@echo 'Invoking: HCS08 Compiler'
	"$(HC08ToolsEnv)/chc08" -ArgFile"Generated_Code/Muestreador.args" -ObjN="Generated_Code/Muestreador_c.obj" "$<" -Lm="$(@:%.obj=%.d)" -LmCfg=xilmou
	@echo 'Finished building: $<'
	@echo ' '

Generated_Code/Parada_c.obj: ../Generated_Code/Parada.c
	@echo 'Building file: $<'
	@echo 'Executing target #20 $<'
	@echo 'Invoking: HCS08 Compiler'
	"$(HC08ToolsEnv)/chc08" -ArgFile"Generated_Code/Parada.args" -ObjN="Generated_Code/Parada_c.obj" "$<" -Lm="$(@:%.obj=%.d)" -LmCfg=xilmou
	@echo 'Finished building: $<'
	@echo ' '

Generated_Code/Right_Motor_c.obj: ../Generated_Code/Right_Motor.c
	@echo 'Building file: $<'
	@echo 'Executing target #21 $<'
	@echo 'Invoking: HCS08 Compiler'
	"$(HC08ToolsEnv)/chc08" -ArgFile"Generated_Code/Right_Motor.args" -ObjN="Generated_Code/Right_Motor_c.obj" "$<" -Lm="$(@:%.obj=%.d)" -LmCfg=xilmou
	@echo 'Finished building: $<'
	@echo ' '

Generated_Code/Right_Motor_Ref_c.obj: ../Generated_Code/Right_Motor_Ref.c
	@echo 'Building file: $<'
	@echo 'Executing target #22 $<'
	@echo 'Invoking: HCS08 Compiler'
	"$(HC08ToolsEnv)/chc08" -ArgFile"Generated_Code/Right_Motor_Ref.args" -ObjN="Generated_Code/Right_Motor_Ref_c.obj" "$<" -Lm="$(@:%.obj=%.d)" -LmCfg=xilmou
	@echo 'Finished building: $<'
	@echo ' '

Generated_Code/Sensores_c.obj: ../Generated_Code/Sensores.c
	@echo 'Building file: $<'
	@echo 'Executing target #23 $<'
	@echo 'Invoking: HCS08 Compiler'
	"$(HC08ToolsEnv)/chc08" -ArgFile"Generated_Code/Sensores.args" -ObjN="Generated_Code/Sensores_c.obj" "$<" -Lm="$(@:%.obj=%.d)" -LmCfg=xilmou
	@echo 'Finished building: $<'
	@echo ' '

Generated_Code/Vectors_c.obj: ../Generated_Code/Vectors.c
	@echo 'Building file: $<'
	@echo 'Executing target #24 $<'
	@echo 'Invoking: HCS08 Compiler'
	"$(HC08ToolsEnv)/chc08" -ArgFile"Generated_Code/Vectors.args" -ObjN="Generated_Code/Vectors_c.obj" "$<" -Lm="$(@:%.obj=%.d)" -LmCfg=xilmou
	@echo 'Finished building: $<'
	@echo ' '


