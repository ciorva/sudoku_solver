
set(sudokusol_src 
	main.cpp
	main_window.cpp
	sudoku_solver.cpp
)

set(sudoku_h
	main_window.hpp
	sudoku_solver.h
)

ADD_EXECUTABLE(sudokusol ${sudokusol_src} ${sudokusol_h})

# Link the target to the GTKMM libraries
target_link_libraries(sudokusol 
	${GTKMM_LIBRARIES}
	glpk
	m
)
