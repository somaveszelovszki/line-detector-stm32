/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */     

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */

/* USER CODE END Variables */
osThreadId SensorTaskHandle;
uint32_t SensorTaskBuffer[ 1024 ];
osStaticThreadDef_t SensorTaskControlBlock;
osThreadId LineCalcTaskHandle;
uint32_t LineCalcTaskBuffer[ 1024 ];
osStaticThreadDef_t LineCalcTaskControlBlock;
osThreadId DebugTaskHandle;
uint32_t DebugTaskBuffer[ 1024 ];
osStaticThreadDef_t DebugTaskControlBlock;

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */
void runSensorTask(void);
void runLineCalcTask(void);
void runDebugTask(void);
/* USER CODE END FunctionPrototypes */

void StartSensorTask(void const * argument);
void StartLineCalcTask(void const * argument);
void StartDebugTask(void const * argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/* GetIdleTaskMemory prototype (linked to static allocation support) */
void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize );

/* Hook prototypes */
void vApplicationStackOverflowHook(xTaskHandle xTask, signed char *pcTaskName);

/* USER CODE BEGIN 4 */
__weak void vApplicationStackOverflowHook(xTaskHandle xTask, signed char *pcTaskName)
{
   /* Run time stack overflow checking is performed if
   configCHECK_FOR_STACK_OVERFLOW is defined to 1 or 2. This hook function is
   called if a stack overflow is detected. */
}
/* USER CODE END 4 */

/* USER CODE BEGIN GET_IDLE_TASK_MEMORY */
static StaticTask_t xIdleTaskTCBBuffer;
static StackType_t xIdleStack[configMINIMAL_STACK_SIZE];
  
void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize )
{
  *ppxIdleTaskTCBBuffer = &xIdleTaskTCBBuffer;
  *ppxIdleTaskStackBuffer = &xIdleStack[0];
  *pulIdleTaskStackSize = configMINIMAL_STACK_SIZE;
  /* place for user code */
}                   
/* USER CODE END GET_IDLE_TASK_MEMORY */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */
       
  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* definition and creation of SensorTask */
  osThreadStaticDef(SensorTask, StartSensorTask, osPriorityNormal, 0, 1024, SensorTaskBuffer, &SensorTaskControlBlock);
  SensorTaskHandle = osThreadCreate(osThread(SensorTask), NULL);

  /* definition and creation of LineCalcTask */
  osThreadStaticDef(LineCalcTask, StartLineCalcTask, osPriorityNormal, 0, 1024, LineCalcTaskBuffer, &LineCalcTaskControlBlock);
  LineCalcTaskHandle = osThreadCreate(osThread(LineCalcTask), NULL);

  /* definition and creation of DebugTask */
  osThreadStaticDef(DebugTask, StartDebugTask, osPriorityLow, 0, 1024, DebugTaskBuffer, &DebugTaskControlBlock);
  DebugTaskHandle = osThreadCreate(osThread(DebugTask), NULL);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

}

/* USER CODE BEGIN Header_StartSensorTask */
/**
  * @brief  Function implementing the SensorTask thread.
  * @param  argument: Not used 
  * @retval None
  */
/* USER CODE END Header_StartSensorTask */
void StartSensorTask(void const * argument)
{
    
    
    
    

  /* USER CODE BEGIN StartSensorTask */
  UNUSED(argument);
  runSensorTask();
  vTaskDelete(NULL);
  /* USER CODE END StartSensorTask */
}

/* USER CODE BEGIN Header_StartLineCalcTask */
/**
* @brief Function implementing the LineCalcTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartLineCalcTask */
void StartLineCalcTask(void const * argument)
{
  /* USER CODE BEGIN StartLineCalcTask */
  UNUSED(argument);
  runLineCalcTask();
  vTaskDelete(NULL);
  /* USER CODE END StartLineCalcTask */
}

/* USER CODE BEGIN Header_StartDebugTask */
/**
* @brief Function implementing the DebugTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartDebugTask */
void StartDebugTask(void const * argument)
{
  /* USER CODE BEGIN StartDebugTask */
  UNUSED(argument);
  runDebugTask();
  vTaskDelete(NULL);
  /* USER CODE END StartDebugTask */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */
     
/* USER CODE END Application */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
