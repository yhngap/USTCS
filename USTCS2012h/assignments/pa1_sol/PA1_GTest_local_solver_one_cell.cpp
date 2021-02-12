//#include <chrono>
//#include <iostream>
//#include <set>
//#include <utility>
#include "gtest/gtest.h"
#include "PA1.h"
#include "PA1_sol.h"
using namespace std;

// Game State Variables.
Cell grid[MAX_ROWS][MAX_COLS];
bool has_mine[MAX_ROWS][MAX_COLS]; // Default value of false.
int game_stats[5]; // num_rows, num_cols, num_flags_left, num_safe_reveals_left, num_incorrect_flags.
bool mine_exploded = false;



// Helper functions.
//void display_grid_or_sol(Cell grid_input[MAX_ROWS][MAX_COLS], int game_stats_input[5]) {
//	cout << '\n';
//	cout << "  ";
//	for (int col = 0; col < game_stats_input[1]; col += 1) {
//		cout << ' ' << char(col + 'A');
//	}
//	cout << '\n';
//
//	for (int row = 0; row < game_stats_input[0]; row += 1) {
//		if (row < 9) {
//			cout << ' ';
//		}
//		cout << row + 1;
//
//		for (int col = 0; col < game_stats_input[1]; col += 1) {
//			cout << ' ';
//			switch (grid_input[row][col]) {
//			case HIDDEN:
//				cout << 'o';
//				break;
//			case FLAGGED:
//				cout << 'x';
//				break;
//			case SAFE:
//				cout << '?';
//				break;
//			case MINE:
//				cout << '!';
//				break;
//			case ZERO:
//				cout << '.';
//				break;
//			default:
//				cout << grid_input[row][col]; // Unscoped enum implicit conversion to int.
//			}
//		}
//		cout << '\n';
//	}
//
//	cout << '\n';
//	cout << "Flags Left: " << game_stats_input[2] << '\n';
//	cout << "Safe cells left: " << game_stats_input[3] << '\n';
//	cout << "Incorrect flags: " << game_stats_input[4] << '\n';
//	cout << '\n';
//}

void reset_grid_layout(Cell layout_to_reset[MAX_ROWS][MAX_COLS]) {
	for (int row = 0; row < MAX_ROWS; row += 1) {
		for (int col = 0; col < MAX_COLS; col += 1) {
			layout_to_reset[row][col] = HIDDEN;
		}
	}
}

void reset_mine_layout(bool layout_to_reset[MAX_ROWS][MAX_COLS]) {
	for (int row = 0; row < MAX_ROWS; row += 1) {
		for (int col = 0; col < MAX_COLS; col += 1) {
			layout_to_reset[row][col] = false;
		}
	}
}

void reset_all() {
	reset_grid_layout(grid);
	reset_mine_layout(has_mine);
	game_stats[0] = game_stats[1] = game_stats[2] = game_stats[3] = game_stats[4] = 0;
	mine_exploded = false;

	reset_grid_layout(grid_sol);
	reset_mine_layout(has_mine_sol);
	game_stats_sol[0] = game_stats_sol[1] = game_stats_sol[2] = game_stats_sol[3] = game_stats_sol[4] = 0;
	mine_exploded_sol = false;
}


void copy_grid_layout(Cell layout_overwritten[MAX_ROWS][MAX_COLS], Cell layout_input[MAX_ROWS][MAX_COLS]) {
	for (int row = 0; row < MAX_ROWS; row += 1) {
		for (int col = 0; col < MAX_COLS; col += 1) {
			layout_overwritten[row][col] = layout_input[row][col];
		}
	}
}

void copy_mine_layout(bool layout_overwritten[MAX_ROWS][MAX_COLS], bool layout_input[MAX_ROWS][MAX_COLS]) {
	for (int row = 0; row < MAX_ROWS; row += 1) {
		for (int col = 0; col < MAX_COLS; col += 1) {
			layout_overwritten[row][col] = layout_input[row][col];
		}
	}
}

void copy_sol_to_current_state() {
	copy_grid_layout(grid, grid_sol);
	copy_mine_layout(has_mine, has_mine_sol);
	for (int i = 0; i < 5; i += 1) {
		game_stats[i] = game_stats_sol[i];
	}
	mine_exploded = mine_exploded_sol;
}

//void generate_random_mine_layout(int num_rows, int num_cols, int num_mines, unsigned int seed, bool has_mine_output[MAX_ROWS][MAX_COLS]) {
//	reset_mine_layout(has_mine_output);
//	srand(seed);
//	for (int n = 0; n < num_mines; n += 1) {
//		int row = rand() % num_rows;
//		int col = rand() % num_cols;
//
//		// If already have a mine in this location, increment col and wrap-around in row-major order.
//		while (has_mine_output[row][col]) {
//			row = (row + ((col+1)/num_cols)) % num_rows;
//			col = (col+1) % num_cols;
//		}
//		has_mine_output[row][col] = true;
//	}
//}




/**************************
 * Task 3: local_solver() *
 **************************/
TEST(LocalSolver, GeneralGridOneCellPerCall) {
	// Grid Setup.
	reset_all();

	bool has_mine_copy[MAX_ROWS][MAX_COLS] = {
		{false, false, false, true , false, false, true , false, false, true , false, false, false, false, false, false, true , false, false, true , false, false, false, false, false},
		{false, false, false, false, false, true , false, true , true , false, false, false, false, false, false, false, true , false, false, false, false, false, false, false, false},
		{true , false, false, false, false, false, false, false, false, false, false, false, false, true , true , false, false, false, false, true , false, false, false, false, false},
		{false, false, false, false, true , false, true , true , true , false, false, false, false, false, false, true , false, true , false, false, true , false, false, false, false},
		{false, false, false, false, false, false, false, false, false, false, false, true , false, true , false, true , false, false, false, false, true , false, false, false, true },
		{false, false, false, false, false, true , false, true , false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false},
		{false, false, false, false, false, false, false, false, false, true , false, false, false, false, true , false, false, false, true , false, false, false, false, false, false},
		{true , false, false, false, false, false, true , true , false, false, true , false, false, false, false, false, false, false, false, false, false, true , false, false, false},
		{false, true , false, false, false, false, false, false, false, false, false, false, true , false, false, false, true , false, false, false, false, false, false, true , false},
		{true,  false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, true , true , false},
		{false, false, false, false, false, false, false, false, true , false, false, false, false, false, true , false, true , false, false, false, false, false, true , true , false},
		{false, false, false, false, false, false, false, false, false, false, true , false, false, false, false, false, true , false, true , false, false, false, false, false, false},
		{false, false, false, false, false, false, false, false, true , false, false, true , false, false, false, false, true , false, false, false, true , false, false, false, false},
		{false, true , true , false, false, false, false, false, false, false, false, false, false, true , false, false, false, true , false, true , false, false, false, false, false},
		{false, false, false, false, false, false, true , false, false, false, false, false, true , true , false, false, false, false, false, true , false, false, false, false, true },
		{false, false, false, false, false, false, false, false, false, false, false, false, true , false, false, false, false, true , false, false, false, false, false, false, false},
		{false, false, false, false, false, false, false, true , false, false, false, false, false, false, true , false, true , false, true , false, false, false, false, false, true },
		{true , false, true , false, false, false, false, false, false, false, false, false, false, false, true , false, false, true , false, false, false, true , false, false, false},
		{false, true , true , true , false, false, false, false, false, true , true , false, false, true , true , false, true , false, true , false, true , true , false, false, false},
		{false, false, false, false, true , false, false, false, false, false, false, false, false, false, false, false, false, false, true , false, false, true , false, false, false},
		{false, false, true , true , false, false, true , true , false, true , false, true , false, false, false, false, false, false, false, false, false, false, false, true , false},
		{false, false, false, true , false, false, true , false, false, true , true , false, false, false, true , false, false, true , false, true , false, false, false, true , true },
		{false, false, false, false, false, true , true , true , false, false, true , false, false, false, false, false, false, true , false, false, true , false, false, false, false},
		{false, false, false, false, false, false, false, true , true , false, false, false, false, false, false, false, false, false, false, false, true , false, false, false, false},
		{true , true , false, true , false, false, true , true , false, false, true , false, false, false, false, false, false, true , false, false, true , true , false, true , false}
	};
	copy_mine_layout(has_mine_sol, has_mine_copy);

	game_stats_sol[0] = game_stats_sol[1] = 25;
	game_stats_sol[2] = 125;
	game_stats_sol[3] = game_stats_sol[0] * game_stats_sol[1] - game_stats_sol[2];
	game_stats_sol[4] = 0;
	mine_exploded_sol = false;

	copy_sol_to_current_state();

	// Reveal part of the grid and run local_solver().
	//reveal(0, 0);
	reveal_sol(0, 0);
	//reveal(2, 2);
	reveal_sol(2, 2);
	copy_sol_to_current_state();

	// Solution.
	bool local_solver_return_sol = true;
	while (local_solver_return_sol) {
		int cells_to_reveal_sol[MAX_CELLS][2] = {};
		int cells_to_flag_sol[MAX_CELLS][2] = {};
		int num_cells_sol[2] = {};
		local_solver_return_sol = local_solver_sol(cells_to_reveal_sol, cells_to_flag_sol, num_cells_sol);

		for (int i = 0; i < num_cells_sol[0]; i += 1) {
			reveal_sol(cells_to_reveal_sol[i][0], cells_to_reveal_sol[i][1]);
		}
		for (int i = 0; i < num_cells_sol[1]; i += 1) {
			flag_sol(cells_to_flag_sol[i][0], cells_to_flag_sol[i][1]);
		}

		// Uncomment to display sol at each iteration.
//		cout << '\n';
//		cout << "Grid Solution: ";
//		display_grid_or_sol(grid_sol, game_stats_sol);
//		cout << '\n';
	}

	// Submission.
	bool local_solver_return = true;
	while (local_solver_return) {
		int cells_to_reveal[MAX_CELLS][2] = {};
		int cells_to_flag[MAX_CELLS][2] = {};
		int num_cells[2] = {};
		local_solver_return = local_solver(cells_to_reveal, cells_to_flag, num_cells);

		for (int i = 0; i < num_cells[0]; i += 1) {
			reveal(cells_to_reveal[i][0], cells_to_reveal[i][1]);
		}
		for (int i = 0; i < num_cells[1]; i += 1) {
			flag(cells_to_flag[i][0], cells_to_flag[i][1]);
		}

		// Uncomment to display grid at each iteration.
//		cout << '\n';
//		cout << "Actual Grid: ";
//		display_grid_or_sol(grid, game_stats);
//		cout << '\n';
	}

	// Compare final grid state between submission and solution.
	for (int row = 0; row < game_stats_sol[0]; row += 1) {
		for (int col = 0; col < game_stats_sol[1]; col += 1) {
			EXPECT_EQ(grid[row][col], grid_sol[row][col]);
		}
	}
}
