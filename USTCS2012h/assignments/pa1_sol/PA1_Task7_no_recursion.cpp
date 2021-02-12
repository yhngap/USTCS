#include "PA1.h"

/***********************************************************************
 * TODO 1: Reveal the specified cell.
 * - If the cell is already revealed, do nothing.
 * - If the cell has a mine, display it and set mine_exploded.
 * - If the cell is not a mine, update num_safe_reveals_left in
 *   game_stats[3], and display the number of neighbor mines.
 * - If there are no neighboring mines, unflag and reveal all neighbors.
 * Note: Be careful not to multi-count when updating game_stats[3].
 ***********************************************************************/
void reveal(int row, int col) {
	// If the cell is already revealed, do nothing.
	if (grid[row][col] >= 0) {
		return;
	}

	// If the cell has a mine, display it and set mine_exploded.
	if (has_mine[row][col]) {
		grid[row][col] = MINE;
		mine_exploded = true;
		return;
	}

	game_stats[3] -= 1; // Update num_safe_reveals_left in game_stats[3].

	// Display the number of neighbor mines.
	int num_neighbor_mines = 0;
	for (int i = row-1; i <= row+1; i += 1) {
		for (int j = col-1; j <= col+1; j += 1) {
			if (i >= 0 && i < game_stats[0] && j >= 0 && j < game_stats[1]) {
				if (has_mine[i][j]) {
					num_neighbor_mines += 1;
				}
			}
		}
	}
	grid[row][col] = Cell(num_neighbor_mines); // type-cast to Cell enum-type.

	// If there are no neighboring mines, unflag and reveal all neighbors.
	if (num_neighbor_mines == 0) {
		for (int i = row-1; i <= row+1; i += 1) {
			for (int j = col-1; j <= col+1; j += 1) {
				if (i >= 0 && i < game_stats[0] && j >= 0 && j < game_stats[1]) {
					if (grid[i][j] == FLAGGED) {
						flag(i, j);
					}
					if (grid[i][j] == HIDDEN) {
						reveal(i, j);
					}
				}
			}
		}
	}
}

/***********************************************************************
 * TODO 2: Toggle the flagging of the specified cell.
 * - If the specified cell is hidden, flag it, and vice versa.
 * - Update num_flags_left in game_stats[2].
 * - Update num_incorrect_flags in game_stats[4].
 ***********************************************************************/
void flag(int row, int col) {
	if (grid[row][col] == HIDDEN) {
		grid[row][col] = FLAGGED;
		game_stats[2] -= 1;
		if (!has_mine[row][col]) {
			game_stats[4] += 1;
		}
	} else if (grid[row][col] == FLAGGED) {
		grid[row][col] = HIDDEN;
		game_stats[2] += 1;
		if (!has_mine[row][col]) {
			game_stats[4] -= 1;
		}
	}
}

/***********************************************************************
 * TODO 3: Determine hidden cells to reveal and to flag, considering
 * only one constraint at a time.
 * - If the number of flagged cells surrounding a constraint is equal to
 *   the constraint, then reveal all surrounding unflagged hidden cells.
 * - If the number of hidden + flagged cells surrounding a constraint is equal to
 *   the constraint, then flag all surrounding unflagged hidden cells.
 * - Return whether or not these two rules are successful in
 *   determining at least one cell to reveal or to flag.
 ***********************************************************************/
bool local_solver(int cells_to_reveal[MAX_CELLS][2], int cells_to_flag[MAX_CELLS][2], int num_cells[2]) {
	num_cells[0] = num_cells[1] = 0;

	bool must_be_revealed[MAX_ROWS][MAX_COLS] = {}; // Initialized to all false.
	bool must_be_flagged[MAX_ROWS][MAX_COLS] = {}; // Initialized to all false.
	for (int row = 0; row < game_stats[0]; row += 1) {
		for (int col = 0; col < game_stats[1]; col += 1) {
			// A revealed safe cell with a number is a constraint.
			if (grid[row][col] > 0)	{
				int num_hidden_cells = 0;
				int num_flagged_cells = 0;

				// Count all hidden and flagged neighbor cells.
				for (int i = row-1; i <= row+1; i += 1) {
					for (int j = col-1; j <= col+1; j += 1) {
						if (i >= 0 && i < game_stats[0] && j >= 0 && j < game_stats[1]) {
							if (grid[i][j] == HIDDEN) {
								num_hidden_cells += 1;
							} else if (grid[i][j] == FLAGGED) {
								num_flagged_cells += 1;
							}
						}
					}
				}

				// Only do the constraint checking if there actually are surrounding hidden cells.
				if (num_hidden_cells > 0) {
					// If the number of flagged cells surrounding a constraint is equal to the constraint, then reveal all surrounding unflagged hidden cells.
					if (grid[row][col] == num_flagged_cells) {
						for (int i = row-1; i <= row+1; i += 1) {
							for (int j = col-1; j <= col+1; j += 1) {
								if (i >= 0 && i < game_stats[0] && j >= 0 && j < game_stats[1]) {
									if (grid[i][j] == HIDDEN) {
										must_be_revealed[i][j] = true;
									}
								}
							}
						}
					}
					// If the number of hidden + flagged cells surrounding a constraint is equal to the constraint, then flag all surrounding unflagged hidden cells.
					else if (grid[row][col] == num_flagged_cells + num_hidden_cells) {
						for (int i = row-1; i <= row+1; i += 1) {
							for (int j = col-1; j <= col+1; j += 1) {
								if (i >= 0 && i < game_stats[0] && j >= 0 && j < game_stats[1]) {
									if (grid[i][j] == HIDDEN) {
										must_be_flagged[i][j] = true;
									}
								}
							}
						}
					}
				}
			}
		}
	}

	// Convert to unordered sets of cells.
	for (int row = 0; row < game_stats[0]; row += 1) {
		for (int col = 0; col < game_stats[1]; col += 1) {
			if (must_be_revealed[row][col]) {
				cells_to_reveal[num_cells[0]][0] = row;
				cells_to_reveal[num_cells[0]][1] = col;
				num_cells[0] += 1;
			} else if (must_be_flagged[row][col]) {
				cells_to_flag[num_cells[1]][0] = row;
				cells_to_flag[num_cells[1]][1] = col;
				num_cells[1] += 1;
			}
		}
	}

	// Return whether or not these two rules are successful in determining at least one cell to reveal or to flag.
	return (num_cells[0] + num_cells[1] > 0);
}

/***********************************************************************
 * TODO 4: Record all unflagged hidden cells and classify each as
 * either constrained or unconstrained.
 * - If an unflagged hidden cell has a neighboring constraint, record
 *   it as constrained.
 * - If an unflagged hidden cell has no neighboring constraints, record
 *   it as unconstrained.
 ***********************************************************************/
// Helper function for classify_hidden_cells().
bool has_neighbor_constraints(int row, int col) {
	for (int i = row-1; i <= row+1; i += 1) {
		for (int j = col-1; j <= col+1; j += 1) {
			if (i >= 0 && i < game_stats[0] && j >= 0 && j < game_stats[1]) {
				if (grid[i][j] > 0) {
					return true;
				}
			}
		}
	}
	return false;
}

void classify_hidden_cells(int constrained_cells[MAX_CELLS][2], int unconstrained_cells[MAX_CELLS][2], int num_cells[2]) {
	num_cells[0] = num_cells[1] = 0;

	for (int row = 0; row < game_stats[0]; row += 1) {
		for (int col = 0; col < game_stats[1]; col += 1) {
			if (grid[row][col] == HIDDEN) {
				bool has_constraint = has_neighbor_constraints(row, col);
				if (has_constraint) {
					constrained_cells[num_cells[0]][0] = row;
					constrained_cells[num_cells[0]][1] = col;
					num_cells[0] += 1;
				} else {
					unconstrained_cells[num_cells[1]][0] = row;
					unconstrained_cells[num_cells[1]][1] = col;
					num_cells[1] += 1;
				}
			}
		}
	}
}

/***********************************************************************
 * TODO 5: Check whether or not all neighboring constraints of the
 * specified cell can still be satisfied.
 * - Return true if there exists a possible configuration of mines
 *   which agrees with all neighboring constraints, without considering
 *   the total number of mines in the grid. Otherwise, return false.
 *
 * Usage: enumerate_possibilities() will test-set the specified cell as
 * FLAGGED/SAFE, and then call this function to check for validity.
 * Hint: For each of the specified cell (A)'s neighbors (N1 - N8), if Ni
 * is revealed with a number, count Ni's neighboring hidden and flagged
 * cells (one of them is A itself) and check if it is still solvable.
 ***********************************************************************/
bool has_satisfiable_neighbor_constraints(int row, int col) {
	// Neighboring cells.
	for (int i = row-1; i <= row+1; i += 1) {
		for (int j = col-1; j <= col+1; j += 1) {
			if (i >= 0 && i < game_stats[0] && j >= 0 && j < game_stats[1]) {
				if (grid[i][j] > 0) {
					// Neighbors of neighboring cell.
					int num_hidden_cells = 0, num_flagged_cells = 0;
					for (int x = i-1; x <= i+1; x += 1) {
						for (int y = j-1; y <= j+1; y += 1) {
							if (x >= 0 && x < game_stats[0] && y >= 0 && y < game_stats[1]) {
								if (grid[x][y] == HIDDEN) {
									num_hidden_cells += 1;
								} else if (grid[x][y] == FLAGGED) {
									num_flagged_cells += 1;
								}
							}
						}
					}

					// Impossible configuration.
					if (grid[i][j] > num_flagged_cells + num_hidden_cells || grid[i][j] < num_flagged_cells) {
						return false;
					}
				}
			}
		}
	}
	return true;
}

/***********************************************************************
 * TODO 6: Validate and record the current configuration of the
 * constrained cells.
 * - Check if the number of flags used in the current configuration of
 *   the constrained cells is within the lower and upper bounds.
 * - If within, record the SAFE/FLAGGED states of the constrained cells,
 *   and update the lowest and the highest number of flags used across
 *   all recorded configurations so far.
 ***********************************************************************/
void record_possibility(int constrained_cells[MAX_CELLS][2], int num_constrained_cells, int num_flags_bounds_used[4], int num_safe_config_records[MAX_CELLS], int num_flagged_config_records[MAX_CELLS]) {
	// Count the number of flags used in this current configuration.
	int num_flags = 0;
	for (int i = 0; i < num_constrained_cells; i += 1) {
		if (grid[constrained_cells[i][0]][constrained_cells[i][1]] == FLAGGED) {
			num_flags += 1;
		}
	}

	// Check if the number of flags used is within the lower and upper bounds.
	if (num_flags >= num_flags_bounds_used[0] && num_flags <= num_flags_bounds_used[1]) {
		// Record the safe/flagged states of the constrained cells.
		for (int i = 0; i < num_constrained_cells; i += 1) {
			if (grid[constrained_cells[i][0]][constrained_cells[i][1]] == SAFE) {
				num_safe_config_records[i]++;
			} else {
				num_flagged_config_records[i]++;
			}
		}

		// Update the lowest and the highest number of flags used across all recorded configurations so far.
		if (num_flags < num_flags_bounds_used[2]) {
			num_flags_bounds_used[2] = num_flags;
		}
		if (num_flags > num_flags_bounds_used[3]) {
			num_flags_bounds_used[3] = num_flags;
		}
	}
}

/***********************************************************************
 * TODO 7: Enumerate, validate, and record all possible configurations
 * of the constrained cells.
 * - Enumerate through all possibilities of the constrained cells by
 *   setting them one-by-one to FLAGGED/SAFE in the grid, then checking
 *   for validity. Use index to keep track of progress.
 * - Stop and backtrack from the exploration of a configuration, if
 *   setting the current constrained cell as FLAGGED/SAFE causes it to
 *   have unsatisfiable neighbor constraints.
 * - If the exploration of a configuration reaches the end, (i.e. all
 *   constrained cells successfully set to FLAGGED/SAFE while satisfying
 *   all neighboring constraints), validate the number of flags used and
 *   record this configuration of the constrained cells.
 * - Remember to reset the constrained cells back to HIDDEN in the grid
 *   when finished with a configuration.
 *
 * Warning: This function potentially has exponential runtime, as the
 * number of possible configurations is 2^num_constrained if not
 * checking validity via satisfiable neighbor constraints.
 * Note: Good usage of recursion will greatly reduce the amount of
 * coding required to implement this function (The TA solution is
 * shorter than this TODO comment block).
 *
 * Hint: You may draw a "binary branching tree graph" to help you
 * visualize all the configurations as well as the recursion pathways.
 * Example enumeration with 4 constrained cells (2^4 = 16 configurations):
 * START ----> SAFE -----> SAFE -----> SAFE -----> SAFE
 *         |           |           |           |
 *         |           |           |           --> FLAGGED
 *         |           |           |
 *         |           |           --> FLAGGED --> SAFE
 *         |           |                       |
 *         |           |                       --> FLAGGED
 *         |           |
 *         |           --> FLAGGED --> SAFE -----> SAFE
 *         |                       |           |
 *         |                       |           --> FLAGGED
 *         |                       |
 *         |                       --> FLAGGED --> SAFE
 *         |                                   |
 *         |                                   --> FLAGGED
 *         |
 *         --> FLAGGED --> SAFE -----> SAFE -----> SAFE
 *                     |           |           |
 *                     |           |           --> FLAGGED
 *                     |           |
 *                     |           --> FLAGGED --> SAFE
 *                     |                       |
 *                     |                       --> FLAGGED
 *                     |
 *                     --> FLAGGED --> SAFE -----> SAFE
 *                                 |           |
 *                                 |           --> FLAGGED
 *                                 |
 *                                 --> FLAGGED --> SAFE
 *                                             |
 *                                             --> FLAGGED
 ***********************************************************************/
void enumerate_possibilities(int constrained_cells[MAX_CELLS][2], int index, int num_constrained_cells, int num_flags_bounds_used[4], int num_safe_config_records[MAX_CELLS], int num_flagged_config_records[MAX_CELLS]) {
	// Simple array-based stack.
	int index_stack[MAX_CELLS] = {};
	Cell index_settings_stack[MAX_CELLS] = {}; // Keeps track if we are setting this index to FLAGGED/SAFE/HIDDEN.
	int index_stack_size = 0;

	// Push the first constrained cell of index 0 into the stack thrice, as FLAGGED/SAFE/HIDDEN.
	index_stack[index_stack_size] = 0;
	index_settings_stack[index_stack_size] = HIDDEN;
	index_stack_size += 1;

	index_stack[index_stack_size] = 0;
	index_settings_stack[index_stack_size] = SAFE;
	index_stack_size += 1;

	index_stack[index_stack_size] = 0;
	index_settings_stack[index_stack_size] = FLAGGED;
	index_stack_size += 1;

	while (index_stack_size > 0) {
		// Pop from the stack.
		int current_index = index_stack[index_stack_size - 1];
		Cell current_index_setting = index_settings_stack[index_stack_size - 1];
		index_stack_size -= 1;

		// Set the specified cell on the grid accordingly.
		int row = constrained_cells[current_index][0];
		int col = constrained_cells[current_index][1];
		grid[row][col] = current_index_setting;

		// We are done if setting the cell as HIDDEN.
		if (grid[row][col] == HIDDEN) { continue; }

		// Only further process the pathway if FLAGGED or SAFE setting has_satisfiable_neighbor_constraints().
		if (has_satisfiable_neighbor_constraints(row, col)) {
			// Call record_possibility() if already reached the end.
			if (current_index + 1 == num_constrained_cells) {
				record_possibility(constrained_cells, num_constrained_cells, num_flags_bounds_used, num_safe_config_records, num_flagged_config_records);
				continue;
			}

			// Push the next index onto the stack thrice, as FLAGGED/SAFE/HIDDEN.
			index_stack[index_stack_size] = current_index + 1;
			index_settings_stack[index_stack_size] = HIDDEN;
			index_stack_size += 1;

			index_stack[index_stack_size] = current_index + 1;
			index_settings_stack[index_stack_size] = SAFE;
			index_stack_size += 1;

			index_stack[index_stack_size] = current_index + 1;
			index_settings_stack[index_stack_size] = FLAGGED;
			index_stack_size += 1;
		}
	}
}

/***********************************************************************
 * TODO 8: Determine which constrained cells must be revealed or flagged.
 * - If a constrained cell has always been recorded as SAFE, reveal it.
 * - If a constrained cell has always been recorded as FLAGGED, flag it.
 ***********************************************************************/
void handle_constrained_cells(int constrained_cells[MAX_CELLS][2], int num_constrained_cells, int num_safe_config_records[MAX_CELLS], int num_flagged_config_records[MAX_CELLS], int cells_to_reveal[MAX_CELLS][2], int cells_to_flag[MAX_CELLS][2], int num_cells[2]) {
	for (int i = 0; i < num_constrained_cells; i += 1) {
		if (num_flagged_config_records[i] == 0) {
			cells_to_reveal[num_cells[0]][0] = constrained_cells[i][0];
			cells_to_reveal[num_cells[0]][1] = constrained_cells[i][1];
			num_cells[0] += 1;
		} else if (num_safe_config_records[i] == 0) {
			cells_to_flag[num_cells[1]][0] = constrained_cells[i][0];
			cells_to_flag[num_cells[1]][1] = constrained_cells[i][1];
			num_cells[1] += 1;
		}
	}
}

/***********************************************************************
 * TODO 9: Determine if all unconstrained cells must be revealed or flagged.
 * - If the number of flags used in all configurations of the
 *   constrained cells is always equal to the upper bound, then all
 *   unconstrained cells must be revealed.
 * - If the number of flags used in all configurations of the
 *   constrained cells is always equal to the lower bound, then all
 *   unconstrained cells must be flagged.
 ***********************************************************************/
void handle_unconstrained_cells(int unconstrained_cells[MAX_CELLS][2], int num_unconstrained_cells, int num_flags_bounds_used[4], int cells_to_reveal[MAX_CELLS][2], int cells_to_flag[MAX_CELLS][2], int num_cells[2]) {
	if (num_flags_bounds_used[2] == num_flags_bounds_used[1]) {
		for (int i = 0; i < num_unconstrained_cells; i += 1) {
			cells_to_reveal[num_cells[0]][0] = unconstrained_cells[i][0];
			cells_to_reveal[num_cells[0]][1] = unconstrained_cells[i][1];
			num_cells[0] += 1;
		}
	} else if (num_flags_bounds_used[3] == num_flags_bounds_used[0]) {
		for (int j = 0; j < num_unconstrained_cells; j += 1) {
			cells_to_flag[num_cells[1]][0] = unconstrained_cells[j][0];
			cells_to_flag[num_cells[1]][1] = unconstrained_cells[j][1];
			num_cells[1] += 1;
		}
	}
}

/***********************************************************************
 * TODO 10: Determine hidden cells to reveal and to flag, considering
 * all constraints simultaneously.
 * - Record all unflagged hidden cells and classify each as either
 *   constrained or unconstrained.
 * - Calculate the upper and lower bounds on the number of flags used
 *   in the configurations of the constrained cells. Upper bound assumes
 *   all unconstrained cells are safe, while lower bound assumes all
 *   unconstrained cells are mines.
 * - Enumerate and record all possible configurations of the constrained
 *   cells and number of flags used.
 * - Determine which constrained cells must be revealed or flagged.
 * - Determine if all unconstrained cells must be revealed or flagged.
 * - Return whether or not this strategy is successful in determining
 *   at least one cell to reveal or to flag.
 ***********************************************************************/
bool global_solver(int cells_to_reveal[MAX_CELLS][2], int cells_to_flag[MAX_CELLS][2], int num_cells[2]) {
	// Record all unflagged hidden cells and classify each as either constrained or unconstrained.
	int constrained_cells[MAX_CELLS][2];
	int unconstrained_cells[MAX_CELLS][2];
	int num_hidden_cells[2];
	classify_hidden_cells(constrained_cells, unconstrained_cells, num_hidden_cells);

	// Calculate the upper and lower bounds on the number of flags used in the configurations of the constrained cells.
	int num_flags_bounds_used[4];
	num_flags_bounds_used[1] = num_flags_bounds_used[2] = game_stats[2]; // Upper bound.
	num_flags_bounds_used[0] = num_flags_bounds_used[3] = game_stats[2] - num_hidden_cells[1]; // Lower bound.

	// Enumerate and record all possible configurations of the constrained cells and number of flags used.
	int num_safe_config_records[MAX_CELLS] = {}; // Initialized to 0.
	int num_flagged_config_records[MAX_CELLS] = {}; // Initialized to 0.
	enumerate_possibilities(constrained_cells, 0, num_hidden_cells[0], num_flags_bounds_used, num_safe_config_records, num_flagged_config_records);

	// Determine which constrained cells must be revealed or flagged.
	// Determine if all unconstrained cells must be revealed or flagged.
	num_cells[0] = num_cells[1] = 0;
	handle_constrained_cells(constrained_cells, num_hidden_cells[0], num_safe_config_records, num_flagged_config_records, cells_to_reveal, cells_to_flag, num_cells);
	handle_unconstrained_cells(unconstrained_cells, num_hidden_cells[1], num_flags_bounds_used, cells_to_reveal, cells_to_flag, num_cells);

	// Return whether or not this strategy is successful in determining at least one cell to reveal or to flag.
	return (num_cells[0] + num_cells[1] > 0);
}
