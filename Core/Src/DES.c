#include "DES.h"
#include "DisplayData.h"
#include "lcd.h"
#include "parameter.h"
#include "stimer.h"
#include "Accelerometer.h"
#include "Gyro.h"
#include <stdio.h>

#define GYRO_TIME       300
#define ACCEL_TIME      270
#define LOG_TIME        300
#define SCREEN_TIME     300

#define BASE_HORIZONTAL         70
#define SPACE_HORIZONTAL        120

#define BASE_VERTICAL           63
#define SPACE_VERTICAL          60

#define GYRO_T      1
#define ACCEL_T     2

Gyro_Value Gyro;
Accel_Value Accele;

int checkGyro = 0;
int checkAccel = 0;

char rsBuffer[6][10];

static void startGyro(void* data);
static void startAccel(void* data);
static void startLog(void* data);
static void startScreen(void* data);
static void displayHeaderScreen(void);
static void displayValueScreen(void);
static void debug(void);
static void convertINT(int label);


void initGyroTask(void)
{
    GyroInit();
    startTimer(GYRO_TIME, startGyro, NULL);
}

static void startGyro(void* data)
{
    startTimer(GYRO_TIME, startGyro, NULL);

    checkGyro++;
    GetGyroValues(&Gyro.X, &Gyro.Y, &Gyro.Z);
    convertINT(GYRO_T);
    // GetAccelerometerValues(&Accele.X, &Accele.Y, &Accele.Z);
}

void initAccelTask(void)
{
    AccelerometerInit();
    startTimer(ACCEL_TIME, startAccel, NULL);
}

static void startAccel(void* data)
{
    startTimer(ACCEL_TIME, startAccel, NULL);

    checkAccel++;
    GetAccelerometerValues(&Accele.X, &Accele.Y, &Accele.Z);
    convertINT(ACCEL_T);
}

void initLogDataTask(void)
{
    UartInit();
    startTimer(LOG_TIME, startLog, NULL);
}

static void startLog(void* data)
{
    startTimer(LOG_TIME, startLog, NULL);
    DisplayAxisValues(&Gyro, &Accele);
    debug();
}

void initScreenTask(void)
{
    ILI9341_Init();
    ILI9341_FillScreen(ILI9341_GREEN);
    // displayHeaderScreen();
    startTimer(SCREEN_TIME, startScreen, NULL);
}

static void startScreen(void* data)
{
    startTimer(SCREEN_TIME, startScreen, NULL);
    displayHeaderScreen();
    displayValueScreen();
}

static void displayHeaderScreen(void)
{
    ILI9341_WriteString(78, 10, (char*)"Gyro", Font_16x26, ILI9341_WHITE, ILI9341_GREEN);
    ILI9341_WriteString(210, 10, (char*)"Accel", Font_16x26, ILI9341_WHITE, ILI9341_GREEN);

    ILI9341_WriteString(10, 77, (char*)"X", Font_16x26, ILI9341_WHITE, ILI9341_GREEN);
    ILI9341_WriteString(10, 137, (char*)"Y", Font_16x26, ILI9341_WHITE, ILI9341_GREEN);
    ILI9341_WriteString(10, 197, (char*)"Z", Font_16x26, ILI9341_WHITE, ILI9341_GREEN);

    ILI9341_DrawLine(40, 0, 40, 240, ILI9341_WHITE);

    ILI9341_DrawLine(180, 0, 180, 240, ILI9341_WHITE);

    ILI9341_DrawLine(0, 60, 320, 60, ILI9341_WHITE);

    ILI9341_DrawLine(0, 120, 320, 120, ILI9341_WHITE);

    ILI9341_DrawLine(0, 180, 320, 180, ILI9341_WHITE);
}

static void displayValueScreen(void)
{
    ILI9341_FillRectangle(45, 65, 130, 50, ILI9341_GREEN);
    ILI9341_WriteString(78, 77, (char*)rsBuffer[0], Font_16x26, ILI9341_WHITE, ILI9341_GREEN);
    // ILI9341_FillRectangle(45, 65, 130, 50, ILI9341_PINK);

    ILI9341_FillRectangle(45, 125, 130, 50, ILI9341_GREEN);
    ILI9341_WriteString(78, 137, (char*)rsBuffer[1], Font_16x26, ILI9341_WHITE, ILI9341_GREEN);

    ILI9341_FillRectangle(45, 185, 130, 50, ILI9341_GREEN);
    ILI9341_WriteString(78, 197, (char*)rsBuffer[2], Font_16x26, ILI9341_WHITE, ILI9341_GREEN);

    ILI9341_FillRectangle(185, 65, 130, 50, ILI9341_GREEN);
    ILI9341_WriteString(210, 77, (char*)rsBuffer[3], Font_16x26, ILI9341_WHITE, ILI9341_GREEN);

    ILI9341_FillRectangle(185, 125, 130, 50, ILI9341_GREEN);
    ILI9341_WriteString(210, 137, (char*)rsBuffer[4], Font_16x26, ILI9341_WHITE, ILI9341_GREEN);

    ILI9341_FillRectangle(185, 185, 130, 50, ILI9341_GREEN);
    ILI9341_WriteString(210, 197, (char*)rsBuffer[5], Font_16x26, ILI9341_WHITE, ILI9341_GREEN);

    // for(int i = 0; i < 6; i++)
    // {
    //     for(int j = 0; j < 10; j++)
    //     {
    //         rsBuffer[i][j] = 0;
    //     }
    // }
}

static void convertINT(int label)
{
    if(label == GYRO_T)
    {
        sprintf(rsBuffer[0], "%d", Gyro.X);
        sprintf(rsBuffer[1], "%d", Gyro.Y);
        sprintf(rsBuffer[2], "%d", Gyro.Z);
    }
    if(label == ACCEL_T)
    {
        sprintf(rsBuffer[3], "%d", Accele.X);
        sprintf(rsBuffer[4], "%d", Accele.Y);
        sprintf(rsBuffer[5], "%d", Accele.Z);
    }

}

static void debug()
{
    // DisplayAxisValue("Debug", checkGyro, checkAccel);
    SendString(rsBuffer[0]);
    SendString("\r\n");
}