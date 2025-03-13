#include <superkarel.h>

void turn_right(){
   set_step_delay(0);
   turn_left();
   turn_left();
   turn_left();
   set_step_delay(100);
}

void two_step(){
 step();
 step();
}

void while_front_is_clear(){
  while(front_is_clear()){
   step();
  }
}

void while_is_beeper(){
   while(beepers_present()){
      pick_beeper();
   }
}

void vzad(){
   turn_left();
   turn_left();
}
void return_home(){
   while(true){
      if(front_is_blocked() && left_is_blocked()) turn_right();
      else while_front_is_clear();
      if(front_is_blocked() && right_is_blocked() && left_is_blocked()) break;

   }
}

int main() {
   turn_on("task_2.kw");
   set_step_delay(100);
   while(true){
      if(no_beepers_present() && no_beepers_in_bag() && front_is_clear()) step();
      else if(front_is_blocked() && right_is_blocked()) turn_left();
      else if(beepers_present()) while_is_beeper();
      else if(beepers_in_bag()){
         vzad();
         return_home();
         if(front_is_blocked() && right_is_blocked() && left_is_blocked()) break;
      }
   }

   turn_off();
}
