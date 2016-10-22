################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../Sources/CMD_Rx.c" \
"../Sources/Events.c" \
"../Sources/controlador_AGV.c" \
"../Sources/errores.c" \
"../Sources/estados.c" \
"../Sources/linea_parada.c" \
"../Sources/main.c" \
"../Sources/motores.c" \
"../Sources/posicion.c" \
"../Sources/proximidad.c" \
"../Sources/pruebas.c" \

C_SRCS += \
../Sources/CMD_Rx.c \
../Sources/Events.c \
../Sources/controlador_AGV.c \
../Sources/errores.c \
../Sources/estados.c \
../Sources/linea_parada.c \
../Sources/main.c \
../Sources/motores.c \
../Sources/posicion.c \
../Sources/proximidad.c \
../Sources/pruebas.c \

OBJS += \
./Sources/CMD_Rx_c.obj \
./Sources/Events_c.obj \
./Sources/controlador_AGV_c.obj \
./Sources/errores_c.obj \
./Sources/estados_c.obj \
./Sources/linea_parada_c.obj \
./Sources/main_c.obj \
./Sources/motores_c.obj \
./Sources/posicion_c.obj \
./Sources/proximidad_c.obj \
./Sources/pruebas_c.obj \

OBJS_QUOTED += \
"./Sources/CMD_Rx_c.obj" \
"./Sources/Events_c.obj" \
"./Sources/controlador_AGV_c.obj" \
"./Sources/errores_c.obj" \
"./Sources/estados_c.obj" \
"./Sources/linea_parada_c.obj" \
"./Sources/main_c.obj" \
"./Sources/motores_c.obj" \
"./Sources/posicion_c.obj" \
"./Sources/proximidad_c.obj" \
"./Sources/pruebas_c.obj" \

C_DEPS += \
./Sources/CMD_Rx_c.d \
./Sources/Events_c.d \
./Sources/controlador_AGV_c.d \
./Sources/errores_c.d \
./Sources/estados_c.d \
./Sources/linea_parada_c.d \
./Sources/main_c.d \
./Sources/motores_c.d \
./Sources/posicion_c.d \
./Sources/proximidad_c.d \
./Sources/pruebas_c.d \

C_DEPS_QUOTED += \
"./Sources/CMD_Rx_c.d" \
"./Sources/Events_c.d" \
"./Sources/controlador_AGV_c.d" \
"./Sources/errores_c.d" \
"./Sources/estados_c.d" \
"./Sources/linea_parada_c.d" \
"./Sources/main_c.d" \
"./Sources/motores_c.d" \
"./Sources/posicion_c.d" \
"./Sources/proximidad_c.d" \
"./Sources/pruebas_c.d" \

OBJS_OS_FORMAT += \
./Sources/CMD_Rx_c.obj \
./Sources/Events_c.obj \
./Sources/controlador_AGV_c.obj \
./Sources/errores_c.obj \
./Sources/estados_c.obj \
./Sources/linea_parada_c.obj \
./Sources/main_c.obj \
./Sources/motores_c.obj \
./Sources/posicion_c.obj \
./Sources/proximidad_c.obj \
./Sources/pruebas_c.obj \


# Each subdirectory must supply rules for building sources it contributes
Sources/CMD_Rx_c.obj: ../Sources/CMD_Rx.c
	@echo 'Building file: $<'
	@echo 'Executing target #1 $<'
	@echo 'Invoking: HCS08 Compiler'
	"$(HC08ToolsEnv)/chc08" -ArgFile"Sources/CMD_Rx.args" -ObjN="Sources/CMD_Rx_c.obj" "$<" -Lm="$(@:%.obj=%.d)" -LmCfg=xilmou
	@echo 'Finished building: $<'
	@echo ' '

Sources/%.d: ../Sources/%.c
	@echo 'Regenerating dependency file: $@'
	
	@echo ' '

Sources/Events_c.obj: ../Sources/Events.c
	@echo 'Building file: $<'
	@echo 'Executing target #2 $<'
	@echo 'Invoking: HCS08 Compiler'
	"$(HC08ToolsEnv)/chc08" -ArgFile"Sources/Events.args" -ObjN="Sources/Events_c.obj" "$<" -Lm="$(@:%.obj=%.d)" -LmCfg=xilmou
	@echo 'Finished building: $<'
	@echo ' '

Sources/controlador_AGV_c.obj: ../Sources/controlador_AGV.c
	@echo 'Building file: $<'
	@echo 'Executing target #3 $<'
	@echo 'Invoking: HCS08 Compiler'
	"$(HC08ToolsEnv)/chc08" -ArgFile"Sources/controlador_AGV.args" -ObjN="Sources/controlador_AGV_c.obj" "$<" -Lm="$(@:%.obj=%.d)" -LmCfg=xilmou
	@echo 'Finished building: $<'
	@echo ' '

Sources/errores_c.obj: ../Sources/errores.c
	@echo 'Building file: $<'
	@echo 'Executing target #4 $<'
	@echo 'Invoking: HCS08 Compiler'
	"$(HC08ToolsEnv)/chc08" -ArgFile"Sources/errores.args" -ObjN="Sources/errores_c.obj" "$<" -Lm="$(@:%.obj=%.d)" -LmCfg=xilmou
	@echo 'Finished building: $<'
	@echo ' '

Sources/estados_c.obj: ../Sources/estados.c
	@echo 'Building file: $<'
	@echo 'Executing target #5 $<'
	@echo 'Invoking: HCS08 Compiler'
	"$(HC08ToolsEnv)/chc08" -ArgFile"Sources/estados.args" -ObjN="Sources/estados_c.obj" "$<" -Lm="$(@:%.obj=%.d)" -LmCfg=xilmou
	@echo 'Finished building: $<'
	@echo ' '

Sources/linea_parada_c.obj: ../Sources/linea_parada.c
	@echo 'Building file: $<'
	@echo 'Executing target #6 $<'
	@echo 'Invoking: HCS08 Compiler'
	"$(HC08ToolsEnv)/chc08" -ArgFile"Sources/linea_parada.args" -ObjN="Sources/linea_parada_c.obj" "$<" -Lm="$(@:%.obj=%.d)" -LmCfg=xilmou
	@echo 'Finished building: $<'
	@echo ' '

Sources/main_c.obj: ../Sources/main.c
	@echo 'Building file: $<'
	@echo 'Executing target #7 $<'
	@echo 'Invoking: HCS08 Compiler'
	"$(HC08ToolsEnv)/chc08" -ArgFile"Sources/main.args" -ObjN="Sources/main_c.obj" "$<" -Lm="$(@:%.obj=%.d)" -LmCfg=xilmou
	@echo 'Finished building: $<'
	@echo ' '

Sources/motores_c.obj: ../Sources/motores.c
	@echo 'Building file: $<'
	@echo 'Executing target #8 $<'
	@echo 'Invoking: HCS08 Compiler'
	"$(HC08ToolsEnv)/chc08" -ArgFile"Sources/motores.args" -ObjN="Sources/motores_c.obj" "$<" -Lm="$(@:%.obj=%.d)" -LmCfg=xilmou
	@echo 'Finished building: $<'
	@echo ' '

Sources/posicion_c.obj: ../Sources/posicion.c
	@echo 'Building file: $<'
	@echo 'Executing target #9 $<'
	@echo 'Invoking: HCS08 Compiler'
	"$(HC08ToolsEnv)/chc08" -ArgFile"Sources/posicion.args" -ObjN="Sources/posicion_c.obj" "$<" -Lm="$(@:%.obj=%.d)" -LmCfg=xilmou
	@echo 'Finished building: $<'
	@echo ' '

Sources/proximidad_c.obj: ../Sources/proximidad.c
	@echo 'Building file: $<'
	@echo 'Executing target #10 $<'
	@echo 'Invoking: HCS08 Compiler'
	"$(HC08ToolsEnv)/chc08" -ArgFile"Sources/proximidad.args" -ObjN="Sources/proximidad_c.obj" "$<" -Lm="$(@:%.obj=%.d)" -LmCfg=xilmou
	@echo 'Finished building: $<'
	@echo ' '

Sources/pruebas_c.obj: ../Sources/pruebas.c
	@echo 'Building file: $<'
	@echo 'Executing target #11 $<'
	@echo 'Invoking: HCS08 Compiler'
	"$(HC08ToolsEnv)/chc08" -ArgFile"Sources/pruebas.args" -ObjN="Sources/pruebas_c.obj" "$<" -Lm="$(@:%.obj=%.d)" -LmCfg=xilmou
	@echo 'Finished building: $<'
	@echo ' '


