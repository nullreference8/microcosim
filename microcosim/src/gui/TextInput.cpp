#include "src/gui/TextInput.hpp"
#include "src/controller/Mouse.hpp"
#include <cstring>
#include "raylib.h"
namespace gui {
  TextInput::TextInput(std::shared_ptr<std::string> targetString, Rectangle position, int maxInputChars) {
    *Position = position;
    TargetString = targetString;   
    MaxInputChars = maxInputChars; 
  }

  void TextInput::CheckHover(std::shared_ptr<Controller::Mouse> mouse) {
    if(mouse->MouseX > Position->x && mouse->MouseX < Position->x + Position->width && mouse->MouseY > Position->y && mouse->MouseY < Position->y + Position->height) {
      IsMouseHover = true;
    } else {
      IsMouseHover = false;
    }
  }

  void TextInput::Draw() {
    if (IsMouseHover) {
      SetMouseCursor(MOUSE_CURSOR_IBEAM);
    } else {
      SetMouseCursor(MOUSE_CURSOR_DEFAULT);
    }

    DrawRectangleRec(*Position, LIGHTGRAY);

    if (IsMouseHover) { 
      DrawRectangleLines((int)Position->x, (int)Position->y, (int)Position->width, (int)Position->height, RED);
    } else {
      DrawRectangleLines((int)Position->x, (int)Position->y, (int)Position->width, (int)Position->height, DARKGRAY);
    }

    char* txt = strcpy(new char[(*TargetString).size() + 1], (*TargetString).c_str());
    DrawText(txt, (int)Position->x + 5, (int)Position->y + 8, 40, MAROON);

    if (IsMouseHover)
    {
      if (LetterCount < MaxInputChars)
      {
        // Draw blinking underscore char
        if (((FrameCounter/20)%2) == 0) {
          DrawText("|", (int)Position->x + 8 + MeasureText(txt, 40), (int)Position->y + 12, 40, MAROON);
        }
      }
    }
  }

  void TextInput::GetKeyUpdateString() {
    if (FrameCounter > 100) {
      FrameCounter = 0;
    }
    
    int key = GetCharPressed();
    FrameCounter++;

    // Check if more characters have been pressed on the same frame
    LetterCount = TargetString->size();
    while (key > 0)
    {
      // NOTE: Only allow keys in range [32..125]
      if ((key >= 32) && (key <= 125) && (LetterCount < MaxInputChars))
      {
        (*TargetString)[LetterCount] = (char)key;
        (*TargetString)[LetterCount+1] = '\0'; // Add null terminator at the end of the string.
        LetterCount++;
      }

      key = GetCharPressed();  // Check next character in the queue
    }

    if (IsKeyPressed(KEY_BACKSPACE))
    {
      LetterCount--;
      if (LetterCount < 0) {
        LetterCount = 0;
      }

      (*TargetString)[LetterCount] = '\0';
    }
  }
}