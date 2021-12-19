
#include <memory>
#include <string>
class Rectangle;
namespace Controller {
  class Mouse;
}
namespace gui {
  class TextInput {
    TextInput(std::shared_ptr<std::string> targetString, Rectangle position, int maxInputChars);
    std::shared_ptr<Rectangle> Position;
    bool IsMouseHover = false;
    int MaxInputChars = 0;
    int LetterCount = 0;
    int FrameCounter = 0; //For blinking cursor
    std::shared_ptr<std::string> TargetString;
    void CheckHover(std::shared_ptr<Controller::Mouse> mouse);
    void GetKeyUpdateString();
    void Draw();
    //TODO: Add gamestate, make only one input box selectable
  };
}