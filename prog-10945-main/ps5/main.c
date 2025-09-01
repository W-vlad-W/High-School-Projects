#define _GNU_SOURCE 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "game.h"
#include "world.h"
#include "item.h"
#include "backpack.h"
#include "room.h"
#include "command.h"
#include "parser.h"

void demonstrate_container_operations() {
    printf("\n=== Демонстрація роботи з контейнерами ===\n");
    
    struct item* sword = create_item("Sword", "Sharp steel sword", MOVABLE | EXAMINABLE);
    struct item* potion = create_item("Potion", "Healing potion", MOVABLE | USABLE);
    
    struct container* list = create_container(NULL, ITEM, sword);
    list = create_container(list, ITEM, potion);
    
    char* message = strdup("Hello World!");
    list = create_container(list, TEXT, message);
    
    printf("Пошук предмета 'Sword': ");
    struct item* found = (struct item*)get_from_container_by_name(list, "sword");
    if(found) printf("Знайдено: %s\n", found->name);
    else printf("Не знайдено\n");
    
    list = remove_container(list, potion);
    printf("Після видалення зілля, список містить %d елементи\n", 
           (list->next ? 2 : 1));
    
    list = destroy_containers(list);
}

void demonstrate_command_system() {
    printf("\n=== Демонстрація системи команд ===\n");
    
    struct parser* parser = create_parser();
    
    struct command* look = create_command("look", "Look around", "look", 0);
    struct command* take = create_command("take", "Take item", "take [a-zA-Z]+", 1);
    
    parser->commands = create_container(parser->commands, COMMAND, look);
    parser->commands = create_container(parser->commands, COMMAND, take);
    
    printf("Тестування парсера:\n");
    char* test_input1 = strdup("look");
    char* test_input2 = strdup("take sword");
    
    struct command* cmd1 = parse_input(parser, test_input1);
    if(cmd1) printf("Розпізнано команду: %s\n", cmd1->name);
    
    struct command* cmd2 = parse_input(parser, test_input2);
    if(cmd2 && cmd2->groups && cmd2->groups[0]) {
        printf("Розпізнано команду: %s з параметром: %s\n", 
               cmd2->name, cmd2->groups[0]);
    }
    destroy_command(look);
    destroy_command(take);
    free(test_input1);
    free(test_input2);
    parser = destroy_parser(parser);
}

int main() {
    struct game* game = create_game();
    if(!game) {
        fprintf(stderr, "Помилка створення гри\n");
        return EXIT_FAILURE;
    }

    struct room* hall = create_room("Hall", "Великий зал з мармуровими стінами");
    struct room* kitchen = create_room("Kitchen", "Кухня з димовою піччю");
    struct room* garden = create_room("Garden", "Занедбаний сад");
    
    set_exits_from_room(hall, NULL, garden, kitchen, NULL);
    set_exits_from_room(kitchen, NULL, NULL, NULL, hall);
    set_exits_from_room(garden, hall, NULL, NULL, NULL);
    
    game->world = create_world();
    add_room_to_world(game->world, hall);
    add_room_to_world(game->world, kitchen);
    add_room_to_world(game->world, garden);
    game->current_room = hall;
    
    struct item* key = create_item("Key", "Старий ключ", MOVABLE | EXAMINABLE);
    struct item* book = create_item("Book", "Записи старого магістра", EXAMINABLE);
    struct item* apple = create_item("Apple", "Соковите яблуко", MOVABLE | USABLE);
    
    add_item_to_room(hall, key);
    add_item_to_room(kitchen, apple);
    add_item_to_room(garden, book);
    
    game->backpack = create_backpack(3);
    
    demonstrate_container_operations();
    
    demonstrate_command_system();
    
    struct room* found_room = get_room(game->world, "Kitchen");
    if(found_room) {
        printf("\nЗнайдено кімнату: %s\n", found_room->name);
    }
    
    printf("\n=== Початок гри ===\n");
    play_game(game);  
    destroy_item(key);
    destroy_item(book);
    destroy_item(apple);
    destroy_room(hall);
    destroy_room(kitchen);
    destroy_room(garden);
    destroy_world(game->world);
    game = destroy_game(game);
    return EXIT_SUCCESS;
}