#ifndef FTXUI_COMPONENT_SCREEN_INTERACTIVE_HPP
#define FTXUI_COMPONENT_SCREEN_INTERACTIVE_HPP

#include <atomic>
#include <condition_variable>
#include <ftxui/component/receiver.hpp>
#include <functional>
#include <memory>
#include <mutex>
#include <queue>

#include "ftxui/component/event.hpp"
#include "ftxui/screen/screen.hpp"

namespace ftxui {
class Component;

class ScreenInteractive : public Screen {
 public:
  static ScreenInteractive FixedSize(int dimx, int dimy);
  static ScreenInteractive Fullscreen();
  static ScreenInteractive FitComponent();
  static ScreenInteractive TerminalOutput();

  ~ScreenInteractive();
  void Loop(Component*);
  std::function<void()> ExitLoopClosure();

  void PostEvent(Event event);

 private:
  void Draw(Component* component);
  void EventLoop(Component* component);

  enum class Dimension {
    FitComponent,
    Fixed,
    Fullscreen,
    TerminalOutput,
  };
  Dimension dimension_ = Dimension::Fixed;
  ScreenInteractive(int dimx, int dimy, Dimension dimension);

  Sender<Event> event_sender_;
  Receiver<Event> event_receiver_;

  std::string set_cursor_position;
  std::string reset_cursor_position;

  std::atomic<bool> quit_ = false;
};

}  // namespace ftxui

#endif /* end of include guard: FTXUI_COMPONENT_SCREEN_INTERACTIVE_HPP */
