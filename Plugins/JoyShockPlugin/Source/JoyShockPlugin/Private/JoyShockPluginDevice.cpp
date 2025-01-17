#include "JoyShockPluginDevice.h"
#include "JoyShockPlugin.h"
#include "JoyShockFunctions.h"
#include "JoyShockLibrary.h"
#include "Runtime/InputCore/Classes/InputCoreTypes.h"
#include "core.h"

const FKey TestKey("TestKey");
const FKey TestAxis("TestAXIS");

// Input FKey aggiuntivi: al momento non ci importa se sono levette, giroscopi o pulsanti.
// Sintassi: niente spazi. La stringa e il nome della FKey devono essere uguali.

//----------------- Joy-Con L
// Leve
const FKey JoyCon_L_ThumbstickXAxis("JoyCon_L_ThumbstickXAxis");
const FKey JoyCon_L_ThumbstickYAxis("JoyCon_L_ThumbstickYAxis");

// Pulsanti. Similmente alla sintassi di Jsl, uso NSWE per indicare i pulsanti evitando confusioni come A/B, X/Y, X (Nintendo)/X (Playstation)...
const FKey JoyCon_L_Up("JoyCon_L_Up");
const FKey JoyCon_L_Down("JoyCon_L_Down");
const FKey JoyCon_L_Left("JoyCon_L_Left");
const FKey JoyCon_L_Right("JoyCon_L_Right");

const FKey JoyCon_L_Shoulder("JoyCon_L_Shoulder");
const FKey JoyCon_L_Trigger("JoyCon_L_Trigger");

const FKey JoyCon_L_ThumbstickButton("JoyCon_L_ThumbstickButton");
const FKey JoyCon_L_Capture("JoyCon_L_Capture");
const FKey JoyCon_L_Special("JoyCon_L_Special"); // Quel pulsante "-".

const FKey JoyCon_L_SideL("JoyCon_L_SideL");
const FKey JoyCon_L_SideR("JoyCon_L_SideR");

// Movimento. Per effettuare l'output di vettori al sistema di input, sarebbe necessario Axis3D di Enhanced Input Subsystem (UE5). Ma qui ci arrangiamo...
const FKey JoyCon_L_GyroX("JoyCon_L_GyroX");
const FKey JoyCon_L_AccumulGyroX("JoyCon_L_AccumulGyroX");
const FKey JoyCon_L_GyroY("JoyCon_L_GyroY");
const FKey JoyCon_L_AccumulGyroY("JoyCon_L_AccumulGyroY");
const FKey JoyCon_L_GyroZ("JoyCon_L_GyroZ");
const FKey JoyCon_L_AccumulGyroZ("JoyCon_L_AccumulGyroZ");
const FKey JoyCon_L_AccelX("JoyCon_L_AccelX");
const FKey JoyCon_L_AccelY("JoyCon_L_AccelY");
const FKey JoyCon_L_AccelZ("JoyCon_L_AccelZ");
const FKey JoyCon_L_GravX("JoyCon_L_GravX");
const FKey JoyCon_L_GravY("JoyCon_L_GravY");
const FKey JoyCon_L_GravZ("JoyCon_L_GravZ");


//----------------- Joy-Con R
// Leve
const FKey JoyCon_R_ThumbstickXAxis("JoyCon_R_ThumbstickXAxis");
const FKey JoyCon_R_ThumbstickYAxis("JoyCon_R_ThumbstickYAxis");

// Pulsanti. Similmente alla sintassi di Jsl, uso NSWE per indicare i pulsanti evitando confusioni come A/B, X/Y, X (Nintendo)/X (Playstation)...
const FKey JoyCon_R_North("JoyCon_R_North");
const FKey JoyCon_R_South("JoyCon_R_South");
const FKey JoyCon_R_West("JoyCon_R_West");
const FKey JoyCon_R_East("JoyCon_R_East");

const FKey JoyCon_R_Shoulder("JoyCon_R_Shoulder");
const FKey JoyCon_R_Trigger("JoyCon_R_Trigger");

const FKey JoyCon_R_ThumbstickButton("JoyCon_R_ThumbstickButton");
const FKey JoyCon_R_Capture("JoyCon_R_Capture");
const FKey JoyCon_R_Special("JoyCon_R_Special"); // Quel pulsante "+".

const FKey JoyCon_R_SideL("JoyCon_R_SideL");
const FKey JoyCon_R_SideR("JoyCon_R_SideR");

// Movimento
const FKey JoyCon_R_GyroX("JoyCon_R_GyroX");
const FKey JoyCon_R_AccumulGyroX("JoyCon_R_AccumulGyroX");
const FKey JoyCon_R_GyroY("JoyCon_R_GyroY");
const FKey JoyCon_R_AccumulGyroY("JoyCon_R_AccumulGyroY");
const FKey JoyCon_R_GyroZ("JoyCon_R_GyroZ");
const FKey JoyCon_R_AccumulGyroZ("JoyCon_R_AccumulGyroZ");
const FKey JoyCon_R_AccelX("JoyCon_R_AccelX");
const FKey JoyCon_R_AccelY("JoyCon_R_AccelY");
const FKey JoyCon_R_AccelZ("JoyCon_R_AccelZ");
const FKey JoyCon_R_GravX("JoyCon_R_GravX");
const FKey JoyCon_R_GravY("JoyCon_R_GravY");
const FKey JoyCon_R_GravZ("JoyCon_R_GravZ");

const FKey FullLThumbstickXAxis("Full_LThumbstickXAxis");
const FKey FullLThumbstickYAxis("Full_LThumbstickYAxis");
const FKey FullRThumbstickXAxis("Full_RThumbstickXAxis");
const FKey FullRThumbstickYAxis("Full_RThumbstickYAxis");

// --------------------- Variabili copia da UJoyShockFunctions
TMap<int, E_JSP_ControllerType> ControllerMap;
int NumberOfDevices;

// --------------------- Variabili input. Riducono overhead
IMU_STATE ImuFull, ImuLeft, ImuRight;
FVector AccumulGyroL, AccumulGyroR, AccumulGyroFull;
MOTION_STATE MotionFull, MotionLeft, MotionRight;
JOY_SHOCK_STATE StateFull, StateLeft, StateRight;
FVector TiltFull, TiltLeft, TiltRight;

// --------------------- Variabili logica. Confrontano i pulsanti ad ogni frame

TArray < TTuple<int, FKey, bool> > ButtonStateLeft =
{
	MakeTuple(JSMASK_UP,JoyCon_L_Up,false),
	MakeTuple(JSMASK_DOWN,JoyCon_L_Down,false),
	MakeTuple(JSMASK_LEFT,JoyCon_L_Left,false),
	MakeTuple(JSMASK_RIGHT,JoyCon_L_Right,false),
	MakeTuple(JSMASK_L,JoyCon_L_Shoulder,false),
	MakeTuple(JSMASK_ZL,JoyCon_L_Trigger,false),
	MakeTuple(JSMASK_LCLICK,JoyCon_L_ThumbstickButton,false),
	MakeTuple(JSMASK_MINUS,JoyCon_L_Special,false),
	MakeTuple(JSMASK_CAPTURE,JoyCon_L_Capture,false),
	MakeTuple(JSMASK_SL,JoyCon_L_SideL,false),
	MakeTuple(JSMASK_SR,JoyCon_L_SideR,false)
};

TArray < TTuple<int, FKey, bool> > ButtonStateRight =
{
	MakeTuple(JSMASK_N,JoyCon_R_North,false),
	MakeTuple(JSMASK_S,JoyCon_R_South,false),
	MakeTuple(JSMASK_W,JoyCon_R_West,false),
	MakeTuple(JSMASK_E,JoyCon_R_East,false),
	MakeTuple(JSMASK_R,JoyCon_R_Shoulder,false),
	MakeTuple(JSMASK_ZR,JoyCon_R_Trigger,false),
	MakeTuple(JSMASK_RCLICK,JoyCon_R_ThumbstickButton,false),
	MakeTuple(JSMASK_PLUS,JoyCon_R_Special,false),
	MakeTuple(JSMASK_HOME,JoyCon_R_Capture,false),
	MakeTuple(JSMASK_SL,JoyCon_R_SideL,false),
	MakeTuple(JSMASK_SR,JoyCon_R_SideR,false)
};

bool isPressed = false;

FJoyShockPluginDevice::FJoyShockPluginDevice(const TSharedRef<FGenericApplicationMessageHandler>& InMessageHandler)
	:MessageHandler(InMessageHandler)
{
	EKeys::AddKey(FKeyDetails(TestKey, FText::FromString("TestKey"), FKeyDetails::GamepadKey));
	EKeys::AddKey(FKeyDetails(TestAxis, FText::FromString("TestAXIS"), FKeyDetails::FloatAxis));

	// Aggiunta delle nuove FKey a EKeys. Qui specifichiamo:
	// - FKey da abbinare (stesso nome dichiarato su!)
	// - "friendly name" per l'editor (può avere spazi, parentesi, purche' sia ANSI)
	// - tipologia (asse, pulsante, tocco...).

	// -------------------- Joy-Con L
	// Leve
	EKeys::AddKey(FKeyDetails(JoyCon_L_ThumbstickXAxis, FText::FromString("JSP Joy-Con (L) Thumbstick X Axis"), FKeyDetails::FloatAxis));
	EKeys::AddKey(FKeyDetails(JoyCon_L_ThumbstickYAxis, FText::FromString("JSP Joy-Con (L) Thumbstick Y Axis"), FKeyDetails::FloatAxis));
	// Pulsanti
	EKeys::AddKey(FKeyDetails(JoyCon_L_Up, FText::FromString("JSP Joy-Con (L) Up Button"), FKeyDetails::GamepadKey));
	EKeys::AddKey(FKeyDetails(JoyCon_L_Down, FText::FromString("JSP Joy-Con (L) Down Button"), FKeyDetails::GamepadKey));
	EKeys::AddKey(FKeyDetails(JoyCon_L_Left, FText::FromString("JSP Joy-Con (L) Left Button"), FKeyDetails::GamepadKey));
	EKeys::AddKey(FKeyDetails(JoyCon_L_Right, FText::FromString("JSP Joy-Con (L) Right Button"), FKeyDetails::GamepadKey));
	EKeys::AddKey(FKeyDetails(JoyCon_L_Shoulder, FText::FromString("JSP Joy-Con (L) L Button"), FKeyDetails::GamepadKey));
	EKeys::AddKey(FKeyDetails(JoyCon_L_Trigger, FText::FromString("JSP Joy-Con (L) ZL Button"), FKeyDetails::GamepadKey));
	EKeys::AddKey(FKeyDetails(JoyCon_L_ThumbstickButton, FText::FromString("JSP Joy-Con (L) Thumbstick Button"), FKeyDetails::GamepadKey));
	EKeys::AddKey(FKeyDetails(JoyCon_L_Capture, FText::FromString("JSP Joy-Con (L) Capture Button"), FKeyDetails::GamepadKey));
	EKeys::AddKey(FKeyDetails(JoyCon_L_Special, FText::FromString("JSP Joy-Con (L) Minus Button"), FKeyDetails::GamepadKey));
	EKeys::AddKey(FKeyDetails(JoyCon_L_SideL, FText::FromString("JSP Joy-Con (L) SL Button"), FKeyDetails::GamepadKey));
	EKeys::AddKey(FKeyDetails(JoyCon_L_SideR, FText::FromString("JSP Joy-Con (L) SR Button"), FKeyDetails::GamepadKey));
	// Movimento
	EKeys::AddKey(FKeyDetails(JoyCon_L_GyroX, FText::FromString("JSP Joy-Con (L) Gyro X"), FKeyDetails::FloatAxis));
	EKeys::AddKey(FKeyDetails(JoyCon_L_AccumulGyroX, FText::FromString("JSP Joy-Con (L) Accumulated Gyro X"), FKeyDetails::FloatAxis));
	EKeys::AddKey(FKeyDetails(JoyCon_L_GyroY, FText::FromString("JSP Joy-Con (L) Gyro Y"), FKeyDetails::FloatAxis));
	EKeys::AddKey(FKeyDetails(JoyCon_L_AccumulGyroY, FText::FromString("JSP Joy-Con (L) Accumulated Gyro Y"), FKeyDetails::FloatAxis));
	EKeys::AddKey(FKeyDetails(JoyCon_L_GyroZ, FText::FromString("JSP Joy-Con (L) Gyro Z"), FKeyDetails::FloatAxis));
	EKeys::AddKey(FKeyDetails(JoyCon_L_AccumulGyroZ, FText::FromString("JSP Joy-Con (L) Accumulated Gyro Z"), FKeyDetails::FloatAxis));
	EKeys::AddKey(FKeyDetails(JoyCon_L_AccelX, FText::FromString("JSP Joy-Con (L) Accelerometer X"), FKeyDetails::FloatAxis));
	EKeys::AddKey(FKeyDetails(JoyCon_L_AccelY, FText::FromString("JSP Joy-Con (L) Accelerometer Y"), FKeyDetails::FloatAxis));
	EKeys::AddKey(FKeyDetails(JoyCon_L_AccelZ, FText::FromString("JSP Joy-Con (L) Accelerometer Z"), FKeyDetails::FloatAxis));
	EKeys::AddKey(FKeyDetails(JoyCon_L_GravX, FText::FromString("JSP Joy-Con (L) Gravity X"), FKeyDetails::FloatAxis));
	EKeys::AddKey(FKeyDetails(JoyCon_L_GravY, FText::FromString("JSP Joy-Con (L) Gravity Y"), FKeyDetails::FloatAxis));
	EKeys::AddKey(FKeyDetails(JoyCon_L_GravZ, FText::FromString("JSP Joy-Con (L) Gravity Z"), FKeyDetails::FloatAxis));

	// -------------------- Joy-Con R
	// Leve
	EKeys::AddKey(FKeyDetails(JoyCon_R_ThumbstickXAxis, FText::FromString("JSP Joy-Con (R) Thumbstick X Axis"), FKeyDetails::FloatAxis));
	EKeys::AddKey(FKeyDetails(JoyCon_R_ThumbstickYAxis, FText::FromString("JSP Joy-Con (R) Thumbstick Y Axis"), FKeyDetails::FloatAxis));
	// Pulsanti
	EKeys::AddKey(FKeyDetails(JoyCon_R_North, FText::FromString("JSP Joy-Con (R) X Button"), FKeyDetails::GamepadKey));
	EKeys::AddKey(FKeyDetails(JoyCon_R_South, FText::FromString("JSP Joy-Con (R) B Button"), FKeyDetails::GamepadKey));
	EKeys::AddKey(FKeyDetails(JoyCon_R_West, FText::FromString("JSP Joy-Con (R) Y Button"), FKeyDetails::GamepadKey));
	EKeys::AddKey(FKeyDetails(JoyCon_R_East, FText::FromString("JSP Joy-Con (R) A Button"), FKeyDetails::GamepadKey));
	EKeys::AddKey(FKeyDetails(JoyCon_R_Shoulder, FText::FromString("JSP Joy-Con (R) R Button"), FKeyDetails::GamepadKey));
	EKeys::AddKey(FKeyDetails(JoyCon_R_Trigger, FText::FromString("JSP Joy-Con (R) ZR Button"), FKeyDetails::GamepadKey));
	EKeys::AddKey(FKeyDetails(JoyCon_R_ThumbstickButton, FText::FromString("JSP Joy-Con (R) Thumbstick Button"), FKeyDetails::GamepadKey));
	EKeys::AddKey(FKeyDetails(JoyCon_R_Capture, FText::FromString("JSP Joy-Con (R) Capture Button"), FKeyDetails::GamepadKey));
	EKeys::AddKey(FKeyDetails(JoyCon_R_Special, FText::FromString("JSP Joy-Con (R) Minus Button"), FKeyDetails::GamepadKey));
	EKeys::AddKey(FKeyDetails(JoyCon_R_SideL, FText::FromString("JSP Joy-Con (R) SL Button"), FKeyDetails::GamepadKey));
	EKeys::AddKey(FKeyDetails(JoyCon_R_SideR, FText::FromString("JSP Joy-Con (R) SR Button"), FKeyDetails::GamepadKey));
	// Movimento
	EKeys::AddKey(FKeyDetails(JoyCon_R_GyroX, FText::FromString("JSP Joy-Con (R) Gyro X"), FKeyDetails::FloatAxis));
	EKeys::AddKey(FKeyDetails(JoyCon_R_AccumulGyroX, FText::FromString("JSP Joy-Con (R) Accumulated Gyro X"), FKeyDetails::FloatAxis));
	EKeys::AddKey(FKeyDetails(JoyCon_R_GyroY, FText::FromString("JSP Joy-Con (R) Gyro Y"), FKeyDetails::FloatAxis));
	EKeys::AddKey(FKeyDetails(JoyCon_R_AccumulGyroY, FText::FromString("JSP Joy-Con (R) Accumulated Gyro Y"), FKeyDetails::FloatAxis));
	EKeys::AddKey(FKeyDetails(JoyCon_R_GyroZ, FText::FromString("JSP Joy-Con (R) Gyro Z"), FKeyDetails::FloatAxis));
	EKeys::AddKey(FKeyDetails(JoyCon_R_AccumulGyroZ, FText::FromString("JSP Joy-Con (R) Accumulated Gyro Z"), FKeyDetails::FloatAxis));
	EKeys::AddKey(FKeyDetails(JoyCon_R_AccelX, FText::FromString("JSP Joy-Con (R) Accelerometer X"), FKeyDetails::FloatAxis));
	EKeys::AddKey(FKeyDetails(JoyCon_R_AccelY, FText::FromString("JSP Joy-Con (R) Accelerometer Y"), FKeyDetails::FloatAxis));
	EKeys::AddKey(FKeyDetails(JoyCon_R_AccelZ, FText::FromString("JSP Joy-Con (R) Accelerometer Z"), FKeyDetails::FloatAxis));
	EKeys::AddKey(FKeyDetails(JoyCon_R_GravX, FText::FromString("JSP Joy-Con (R) Gravity X"), FKeyDetails::FloatAxis));
	EKeys::AddKey(FKeyDetails(JoyCon_R_GravY, FText::FromString("JSP Joy-Con (R) Gravity Y"), FKeyDetails::FloatAxis));
	EKeys::AddKey(FKeyDetails(JoyCon_R_GravZ, FText::FromString("JSP Joy-Con (R) Gravity Z"), FKeyDetails::FloatAxis));
} 

FJoyShockPluginDevice::~FJoyShockPluginDevice()
{
}

void FJoyShockPluginDevice::Tick(float DeltaTime)
{
	// Qui trasferisco continuamente i dati da JoyShockFunctions e li inserisco in variabili locali, per ridurre l'overhead.
	NumberOfDevices = UJoyShockFunctions::NumberOfDevices;
	ControllerMap = UJoyShockFunctions::ControllerMap;
}

void FJoyShockPluginDevice::SendControllerEvents()
{
	// Questa funzione viene chiamata ogni frame. E' il posto perfetto per fare il polling dei controller e inviare segnali ogni volta che viene premuto o rilasciato un
	// pulsante, o inviare i valori delle levette o del giroscopio.

	MessageHandler->OnControllerAnalog(TestAxis.GetFName(), 0, JslGetAccelX(0));
	
	// Pulsanti:

	// if (pulsante_premuto?)
	// {
	// 	MessageHandler->OnControllerButtonPressed(TestKey.GetFName(), 0, false);
	// }
	// else
	// {
	// 	MessageHandler->OnControllerButtonReleased(TestKey.GetFName(), 0, false);
	// }

	// Avvertenza: questo codice è UN DISASTRO!  --  Be careful: this code is A MESS!

	
	for (TTuple<int, E_JSP_ControllerType> T : ControllerMap)
	{
		switch (T.Value)
		{
		case LeftController:
			// 1. Ottieni i dati
			ImuLeft = JslGetIMUState(T.Key);
			MotionLeft = JslGetMotionState(T.Key);
			StateLeft = JslGetSimpleState(T.Key);
			JslGetAndFlushAccumulatedGyro(T.Key, AccumulGyroL.X, AccumulGyroL.Y, AccumulGyroL.Z);
			// 2. Assi (levette)
			MessageHandler->OnControllerAnalog(JoyCon_L_ThumbstickXAxis.GetFName(), 0, FMath::Pow(StateLeft.stickLX,3));
			MessageHandler->OnControllerAnalog(JoyCon_L_ThumbstickYAxis.GetFName(), 0, FMath::Pow(StateLeft.stickLY,3));
			// 3. Pulsanti (bitmask)
			for (TTuple<int, FKey, bool> & C : ButtonStateLeft)
			{
				if (StateLeft.buttons & C.Get<0>())
				{
					MessageHandler->OnControllerButtonPressed(C.Get<1>().GetFName(), 0, C.Get<2>());
					C.Get<2>() = true;
					FText t = C.Get<1>().GetDisplayName();
				}
				else if (C.Get<2>())
				{
					MessageHandler->OnControllerButtonReleased(C.Get<1>().GetFName(), 0, false);
					C.Get<2>() = false;
					FText t = C.Get<1>().GetDisplayName();
				}
			}
			
			
			/* if (StateLeft.buttons & JSMASK_UP)
			{
			MessageHandler->OnControllerButtonPressed(JoyCon_L_Up.GetFName(), 0, isPressed);
			isPressed = true;
			}
			else if (isPressed)
			{
			MessageHandler->OnControllerButtonReleased(JoyCon_L_Up.GetFName(), 0, false);
			isPressed = false;
			} */


			// 4. Movimento
			MessageHandler->OnControllerAnalog(JoyCon_L_GyroX.GetFName(), 0, ImuLeft.gyroZ);
			MessageHandler->OnControllerAnalog(JoyCon_L_GyroY.GetFName(), 0, ImuLeft.gyroX);
			MessageHandler->OnControllerAnalog(JoyCon_L_GyroZ.GetFName(), 0, -ImuLeft.gyroY);
			MessageHandler->OnControllerAnalog(JoyCon_L_AccumulGyroX.GetFName(), 0, AccumulGyroL.Z);
			MessageHandler->OnControllerAnalog(JoyCon_L_AccumulGyroY.GetFName(), 0, AccumulGyroL.X);
			MessageHandler->OnControllerAnalog(JoyCon_L_AccumulGyroZ.GetFName(), 0, -(AccumulGyroL.Y));
			MessageHandler->OnControllerAnalog(JoyCon_L_AccelX.GetFName(), 0, MotionLeft.accelX);
			MessageHandler->OnControllerAnalog(JoyCon_L_AccelY.GetFName(), 0, MotionLeft.accelZ);
			MessageHandler->OnControllerAnalog(JoyCon_L_AccelZ.GetFName(), 0, MotionLeft.accelY);
			MessageHandler->OnControllerAnalog(JoyCon_L_GravX.GetFName(), 0, MotionLeft.gravX);
			MessageHandler->OnControllerAnalog(JoyCon_L_GravY.GetFName(), 0, MotionLeft.gravZ);
			MessageHandler->OnControllerAnalog(JoyCon_L_GravZ.GetFName(), 0, MotionLeft.gravY);
			
			break;
		case RightController:
			// 1. Ottieni i dati
			ImuRight = JslGetIMUState(T.Key);
			MotionRight = JslGetMotionState(T.Key);
			StateRight = JslGetSimpleState(T.Key);
			JslGetAndFlushAccumulatedGyro(T.Key, AccumulGyroR.X, AccumulGyroR.Y, AccumulGyroR.Z);
			// 2. Assi (levette)
			MessageHandler->OnControllerAnalog(JoyCon_R_ThumbstickXAxis.GetFName(), 0, FMath::Pow(StateRight.stickRX,3));
			MessageHandler->OnControllerAnalog(JoyCon_R_ThumbstickYAxis.GetFName(), 0, FMath::Pow(StateRight.stickRY,3));
			// 3. Pulsanti (bitmask)
			for (TTuple<int, FKey, bool> & C : ButtonStateRight)
			{
				if (StateRight.buttons & C.Get<0>())
				{
					MessageHandler->OnControllerButtonPressed(C.Get<1>().GetFName(), 0, C.Get<2>());
					C.Get<2>() = true;
				}
				else if (C.Get<2>())
				{
					MessageHandler->OnControllerButtonReleased(C.Get<1>().GetFName(), 0, false);
					C.Get<2>() = false;
				}
			}
			// 4. Movimento
			MessageHandler->OnControllerAnalog(JoyCon_R_GyroX.GetFName(), 0, ImuRight.gyroZ);
			MessageHandler->OnControllerAnalog(JoyCon_R_GyroY.GetFName(), 0, ImuRight.gyroZ);
			MessageHandler->OnControllerAnalog(JoyCon_R_GyroZ.GetFName(), 0, -ImuRight.gyroY);
			MessageHandler->OnControllerAnalog(JoyCon_R_AccumulGyroX.GetFName(), 0, AccumulGyroR.Z);
			MessageHandler->OnControllerAnalog(JoyCon_R_AccumulGyroY.GetFName(), 0, AccumulGyroR.X);
			MessageHandler->OnControllerAnalog(JoyCon_R_AccumulGyroZ.GetFName(), 0, -(AccumulGyroR.Y));
			MessageHandler->OnControllerAnalog(JoyCon_R_AccelX.GetFName(), 0, MotionRight.accelX);
			MessageHandler->OnControllerAnalog(JoyCon_R_AccelY.GetFName(), 0, MotionRight.accelZ);
			MessageHandler->OnControllerAnalog(JoyCon_R_AccelZ.GetFName(), 0, MotionRight.accelY);
			MessageHandler->OnControllerAnalog(JoyCon_R_GravX.GetFName(), 0, MotionRight.gravX);
			MessageHandler->OnControllerAnalog(JoyCon_R_GravY.GetFName(), 0, MotionRight.gravZ);
			MessageHandler->OnControllerAnalog(JoyCon_R_GravZ.GetFName(), 0, MotionRight.gravY);
			break;

		case FullController:

			break;
		}
	}
}

void FJoyShockPluginDevice::SetMessageHandler(const TSharedRef< FGenericApplicationMessageHandler >& InMessageHandler)
{
	MessageHandler = InMessageHandler;
}

bool FJoyShockPluginDevice::Exec(UWorld * InWorld, const TCHAR * Cmd, FOutputDevice & Ar)
{
	return false;
}

void FJoyShockPluginDevice::SetChannelValue(int32 ControllerId, FForceFeedbackChannelType ChannelType, float Value)
{
}

void FJoyShockPluginDevice::SetChannelValues(int32 ControllerId, const FForceFeedbackValues & values)
{
}
