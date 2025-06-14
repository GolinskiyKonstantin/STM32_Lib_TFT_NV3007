/*
  ******************************************************************************
  * @file 			( фаил ):   NV3007.h
  * @brief 		( описание ):  	
  ******************************************************************************
  * @attention 	( внимание ):	 author: Golinskiy Konstantin	e-mail: golinskiy.konstantin@gmail.com
  ******************************************************************************
  
 */
 
 
#ifndef _NV3007_H
#define _NV3007_H


/* C++ detection */
#ifdef __cplusplus
extern C {
#endif

// Обязательно нужен #include "main.h" 
// чтоб отдельно не подключать файлы связанные с МК и стандартными библиотеками

#include "main.h"
#include "fonts.h"

#include "stdlib.h"
#include "string.h"
#include "math.h"



//#######  SETUP  ##############################################################################################
		
		//==== выбераем через что будем отправлять через HAL или CMSIS(быстрее) ==================
		//-- нужное оставляем другое коментируем ( важно должно быть только один выбран )---------
		
			// указываем порт SPI для CMSIS ( быстро )-------
			// так как у разных МК разные регистры то в функциях корректируем под свой МК
			// на данный момент есть реализация на серию F1 F4 H7 для выбора серии в функциях
			//	void NV3007_SendCmd(uint8_t Cmd);
			//	void NV3007_SendData(uint8_t Data );
			//	void NV3007_SendDataMASS(uint8_t* buff, size_t buff_size);	
			// комментируем и раскомментируем то что нам нужно, также там же редактируем под свой МК если не работает
			//#define 	NV3007_SPI_CMSIS 	SPI2
			//-----------------------------------------------
			
			// указываем порт SPI для HAL ( медлено )--------
			#define 	NV3007_SPI_HAL 		hspi1
			//-----------------------------------------------
			
		//============================================================================
			
			// выбираем как выводить информацию через буфер кадра или попиксельно ( 1-буфер кадра, 0-попиксельный вывод ) -----
			// через буфер быстре если много информации обнавлять за один раз ( требует много оперативки для массива )
			// по пиксельно рисует онлайн буз буферра если информация обновляеться немного то выгодно испотзовать данный режим
			#define FRAME_BUFFER				1
			//-----------------------------------------------------------------------------------------------------------------
			
			
		//=== указываем порты ( если в кубе назвали их DC RES CS то тогда нечего указывать не нужно )
		#if defined (DC_GPIO_Port)
		#else
			#define DC_GPIO_Port	GPIOC
			#define DC_Pin			GPIO_PIN_5
		#endif
		
		#if defined (RST_GPIO_Port)
		#else
			#define RST_GPIO_Port   GPIOB
			#define RST_Pin			GPIO_PIN_14
		#endif
		
		//--  Cесли используем порт CS для выбора устройства тогда раскомментировать ------------
		// если у нас одно устройство лучше пин CS притянуть к земле( или на порту подать GND )
		
		#define CS_PORT
		
		//----------------------------------------------------------------------------------------
		#ifdef CS_PORT
			#if defined (CS_GPIO_Port)
			#else
				#define CS_GPIO_Port    GPIOB
				#define CS_Pin			GPIO_PIN_12
			#endif
		#endif
		
		//=============================================================================
		
		//==  выбираем дисплей: =======================================================
		//-- нужное оставляем другое коментируем ( важно должно быть только один выбран )---------
		
		#define	NV3007_IS_142X428		// 1.68" 142 x 428 NV3007

		//=============================================================================
		
		
//##############################################################################################################

#ifdef NV3007_SPI_HAL
	extern SPI_HandleTypeDef NV3007_SPI_HAL;
#endif

extern uint16_t NV3007_Width, NV3007_Height;

extern uint16_t NV3007_X_Start;
extern uint16_t NV3007_Y_Start;

#define RGB565(r, g, b)         (((r & 0xF8) << 8) | ((g & 0xFC) << 3) | ((b & 0xF8) >> 3))

#define PI 	3.14159265

//--- готовые цвета ------------------------------
#define   	NV3007_BLACK   			0x0000
#define   	NV3007_BLUE    			0x001F
#define   	NV3007_RED     			0xF800
#define   	NV3007_GREEN   			0x07E0
#define 		NV3007_CYAN    			0x07FF
#define 		NV3007_MAGENTA 			0xF81F
#define 		NV3007_YELLOW  			0xFFE0
#define 		NV3007_WHITE   			0xFFFF
//------------------------------------------------


#define NV3007_SWRESET 						0x01
#define NV3007_SLPIN   						0x10
#define NV3007_SLPOUT  						0x11
#define NV3007_NORON   						0x13
#define NV3007_INVOFF  						0x20
#define NV3007_INVON   						0x21
#define NV3007_DISPOFF 						0x28
#define NV3007_DISPON  						0x29
#define NV3007_CASET   						0x2A
#define NV3007_RASET   						0x2B
#define NV3007_RAMWR   						0x2C
#define NV3007_COLMOD  						0x3A
#define NV3007_MADCTL  						0x36
//-----------------------------------------------

#define DELAY 										0x80

//##############################################################################

//###  параметры дисплея 1.68" 142 x 428 NV3007 ###################################

	// 1.68" 142 x 428 NV3007  display, default orientation

#ifdef NV3007_IS_142X428

	#define NV3007_WIDTH  			428
	#define NV3007_HEIGHT 			142
	#define NV3007_XSTART 			0
	#define NV3007_YSTART 			12
	
#endif
	
//##############################################################################


	
//##############################################################################
//##############################################################################


void NV3007_Init(void);
void NV3007_DrawImage(uint16_t x, uint16_t y, uint16_t w, uint16_t h, const uint16_t* data);	
void NV3007_HardReset(void);
void NV3007_SleepModeEnter( void );
void NV3007_SleepModeExit( void );
void NV3007_ColorModeSet(uint8_t ColorMode);
void NV3007_MemAccessModeSet(uint8_t Rotation, uint8_t VertMirror, uint8_t HorizMirror, uint8_t IsBGR);
void NV3007_InversionMode(uint8_t Mode);
void NV3007_FillScreen(uint16_t color);
void NV3007_Clear(void);
void NV3007_FillRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color);
void NV3007_SetBL(uint8_t Value);
void NV3007_DisplayPower(uint8_t On);
void NV3007_DrawRectangle(int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint16_t color);
void NV3007_DrawRectangleFilled(int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint16_t fillcolor);
void NV3007_DrawLine(int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint16_t color);
void NV3007_DrawLineWithAngle(int16_t x, int16_t y, uint16_t length, double angle_degrees, uint16_t color);
void NV3007_DrawTriangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t x3, uint16_t y3, uint16_t color);
void NV3007_DrawFilledTriangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t x3, uint16_t y3, uint16_t color);
void NV3007_DrawPixel(int16_t x, int16_t y, uint16_t color);
void NV3007_DrawCircleFilled(int16_t x0, int16_t y0, int16_t radius, uint16_t fillcolor);
void NV3007_DrawCircle(int16_t x0, int16_t y0, int16_t radius, uint16_t color);
void NV3007_DrawEllipse(int16_t x0, int16_t y0, int16_t radiusX, int16_t radiusY, uint16_t color);
void NV3007_DrawEllipseFilled(int16_t x0, int16_t y0, int16_t radiusX, int16_t radiusY, uint16_t color);
void NV3007_DrawEllipseFilledWithAngle(int16_t x0, int16_t y0, int16_t radiusX, int16_t radiusY, float angle_degrees, uint16_t color);
void NV3007_DrawEllipseWithAngle(int16_t x0, int16_t y0, int16_t radiusX, int16_t radiusY, float angle_degrees, uint16_t color);
void NV3007_DrawChar(uint16_t x, uint16_t y, uint16_t TextColor, uint16_t BgColor, uint8_t TransparentBg, FontDef_t* Font, uint8_t multiplier, unsigned char ch);
void NV3007_DrawCharWithAngle(uint16_t x, uint16_t y, uint16_t TextColor, uint16_t BgColor, uint8_t TransparentBg, FontDef_t* Font, uint8_t multiplier, double angle_degrees, unsigned char ch);
void NV3007_print(uint16_t x, uint16_t y, uint16_t TextColor, uint16_t BgColor, uint8_t TransparentBg, FontDef_t* Font, uint8_t multiplier, char *str);
void NV3007_printWithAngle(uint16_t x, uint16_t y, uint16_t TextColor, uint16_t BgColor, uint8_t TransparentBg, FontDef_t* Font, uint8_t multiplier, double angle_degrees, char *str);
void NV3007_rotation( uint8_t rotation );
void NV3007_DrawBitmap(int16_t x, int16_t y, const unsigned char* bitmap, int16_t w, int16_t h, uint16_t color);
void NV3007_DrawBitmapWithAngle(int16_t x, int16_t y, const unsigned char* bitmap, int16_t w, int16_t h, uint16_t color, double angle_degrees);
void NV3007_DrawCircleHelper(int16_t x0, int16_t y0, int16_t radius, int8_t quadrantMask, uint16_t color);
void NV3007_DrawFillCircleHelper(int16_t x0, int16_t y0, int16_t r, uint8_t corners, int16_t delta, uint16_t color);
void NV3007_DrawFillRoundRect(int16_t x, int16_t y, uint16_t width, uint16_t height, int16_t cornerRadius, uint16_t color);
void NV3007_DrawRoundRect(int16_t x, int16_t y, uint16_t width, uint16_t height, int16_t cornerRadius, uint16_t color);
void NV3007_DrawArc(int16_t x0, int16_t y0, int16_t radius, int16_t startAngle, int16_t endAngle, uint16_t color, uint8_t thick);
void NV3007_DrawLineThick(int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint16_t color, uint8_t thick);
void NV3007_DrawLineThickWithAngle(int16_t x, int16_t y, int16_t length, double angle_degrees, uint16_t color, uint8_t thick);

#if FRAME_BUFFER
	void NV3007_Update(void);
	void NV3007_ClearFrameBuffer(void);
#endif


/* C++ detection */
#ifdef __cplusplus
}
#endif

#endif	/*	_NV3007_H */

/************************ (C) COPYRIGHT GKP *****END OF FILE****/
