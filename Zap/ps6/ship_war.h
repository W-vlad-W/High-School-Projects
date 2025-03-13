/**
 * Initializes the game boards for both players.
 * Parameters:
 * @param width_of_see  - The width of the game board.
 * @param length_of_see - The length of the game board.
 * @param see_one       - The game board for player one.
 * @param see_two       - The game board for player two.
**/
void initialize_see_for_palyers(const int width_of_see, const int length_of_see, char see_one[width_of_see][length_of_see], char see_two[width_of_see][length_of_see]);

/**
 * Displays the game boards for both players side by side.
 * Parameters:
 * @param width_of_see  - The width of the game board.
 * @param length_of_see - The length of the game board.
 * @param see_one       - The game board for player one.
 * @param see_two       - The game board for player two.
**/
void display_see(const int width_of_see, const int length_of_see, char see_one[width_of_see][length_of_see], char see_two[width_of_see][length_of_see]);

/**
 * Allows players to place their ships on the boards.
 * Parameters:
 * @param width_of_see  - The width of the game board.
 * @param length_of_see - The length of the game board.
 * @param see_one       - The game board for player one.
 * @param see_two       - The game board for player two.
**/
void place_ships(const int width_of_see, const int length_of_see, char see_one[width_of_see][length_of_see], char see_two[width_of_see][length_of_see]);


/** 
 * Automatically places ships for the computer's board.
 * Parameters:
 * @param width_of_see  - The width of the game board.
 * @param length_of_see - The length of the game board.
 * @param see_one       - The game board for player one.
**/
void place_ships_for_PC(const int width_of_see, const int length_of_see, char see_one[width_of_see][length_of_see]);

/** 
 * Manages the player's ship placement process.
 * Parameters:
 * @param width_of_see  - The width of the game board.
 * @param length_of_see - The length of the game board.
 * @param see_one       - The game board for player one.
 * @param see_two       - The game board for player two.
**/
void get_player_placement(const int width_of_see, const int length_of_see, char see_one[width_of_see][length_of_see], char see_two[width_of_see][length_of_see]);


/** 
 * Checks if a specific ship is completely destroyed.
 * Parameters:
 * @param width_of_see  - The width of the game board.
 * @param length_of_see - The length of the game board.
 * @param see           - The game board to check.
 * @param row           - The row of the targeted cell.
 * @param col           - The column of the targeted cell.
 * Returns:
    true if the ship is destroyed, false otherwise.
**/
bool is_ship_destroyed(const int width_of_see, const int length_of_see, char see[width_of_see][length_of_see], int row, int col);


/** 
 * Marks surrounding cells as unavailable after a ship is destroyed.
 * Parameters:
 * @param width_of_see  - The width of the game board.
 * @param length_of_see - The length of the game board.
 * @param see           - The game board to update.
 * @param row           - The row of the targeted cell.
 * @param col           - The column of the targeted cell.
**/
void mark_surrounding_cells(const int width_of_see, const int length_of_see, char see[width_of_see][length_of_see], int row, int col);


/**
 * Checks if cells around a potential ship placement are valid.
 * Parameters:
 * @param width_of_see  - The width of the game board.
 * @param length_of_see - The length of the game board.
 * @param see           - The game board to check.
 * @param row           - The starting row of the potential ship placement.
 * @param col           - The starting column of the potential ship placement.
 * @param size          - The size of the ship to place.
 * @param orientation   - The orientation of the ship (0 for horizontal, 1 for vertical).
 * Returns:
    true if the placement is invalid, false otherwise.
**/
bool check_adjacent_cells(const int width_of_see, const int length_of_see, char see[width_of_see][length_of_see], int row, int col, int size, int orientation);


/** 
 * Handles a single turn in the game.
 * Parameters:
 * @param width_of_see  - The width of the game board.
 * @param length_of_see - The length of the game board.
 * @param see_one       - The current player's game board.
 * @param see_two       - The opponent's game board.
 * @param player        - A pointer to the current player's identifier.
**/
void take_turn(const int width_of_see, const int length_of_see, char see_one[width_of_see][length_of_see], char see_two[width_of_see][length_of_see], int *player);


/** 
 * Checks if a player has won the game by destroying all enemy ships.
 * Parameters:
 * @param width_of_see  - The width of the game board.
 * @param length_of_see - The length of the game board.
 * @param see_two       - The opponent's game board.
 * Returns:   
    true if the player has won, false otherwise.
**/
bool check_win(const int width_of_see, const int length_of_see, char see[width_of_see][length_of_see]);


/**
 * Main function to run the "Ship War" game.
 * Returns:
    An integer indicating the game's outcome.
**/
int run_ship_war();
