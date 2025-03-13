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

void beeper_5(){
   if(beepers_present()){
      pick_beeper();
      if(beepers_present()){
         pick_beeper();
         if(beepers_present()){
            pick_beeper();
            if(beepers_present()){
               pick_beeper();
               if(beepers_present()){
                  pick_beeper();
                  turn_off();
               }
               else while(not_facing_east()){
                  turn_left();
               }
            }
            else while(not_facing_south()){
               turn_left();
            }
         }
         else while(not_facing_west()){
            turn_left();
         }
      }
      else while(not_facing_north()){
         turn_left();
      }
   }
}




int main() {
   turn_on("task_6.kw");
   set_step_delay(100);

   while(true){
      beeper_5();
         while(true){
            if(no_beepers_present()) step();
            else break;
         }
   }
   turn_off();
}
