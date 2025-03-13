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

void face_to_south(){
      while(not_facing_south()){
         turn_left();
      }
}
void jump_over(){
   if(beepers_present()) return;
   if(facing_east()){
      turn_left();
      while(right_is_blocked() && front_is_clear()){
         step();
      }

      turn_right();
      step();
      while(right_is_blocked() && no_beepers_present()){
         step();
      }
      if(beepers_present() && beepers_in_bag()){
         turn_right();
         pick_beeper();
         turn_off();
      }
      turn_right();
      while(no_beepers_present()){
         if(front_is_clear()) step();
         else break;
      }
      turn_left();

   }
   else if(facing_west()){
      turn_right();
      while(left_is_blocked() && no_beepers_present()){
         step();
      }
      if(beepers_present() && beepers_in_bag()){
         turn_left();
         pick_beeper();
         turn_off();
      }
      turn_left();
      step();
      while(left_is_blocked() && no_beepers_present()){
         step();
      }
      turn_left();
      while(no_beepers_present()){
         if(front_is_clear()) step();
         else break;
      }
      turn_right();
      }
}

int main() {
   turn_on("task_1.kw");
   set_step_delay(100);
   if(beepers_present()){
      pick_beeper();
      vzad();
      turn_off();
   }
   put_beeper();
   turn_right();
   while_front_is_clear();
   turn_left();
   if(front_is_clear()) while_front_is_clear();
   else {
      turn_left();
      step();
      turn_right();
   }
   while(true){
      while(no_beepers_present()){
      jump_over();
      while(front_is_clear() && no_beepers_present()){
            step();
         }
      }
      if(beepers_present()) break;
   }

   vzad();
   pick_beeper();

   while(true){
      while(no_beepers_present()){
         if(front_is_clear()) step();
         else break;
      }
      jump_over();
      if(beepers_present()) break;
   }
   pick_beeper();
   turn_off();
}
