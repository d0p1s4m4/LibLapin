## Hanged Bunny Studio Library ------    ---  -- --- -    ---  --    - -- -   -
## Hanged Bunny Studio 2014-2017 ----- -- - -- -  -  -- -- - -- --  -- -- -- --
## ----------------------------------- -- -    - - - -- -- - -- ---- -    -- --
## ----------------------------------    -- -- - --- -    ---  --   -- -- -   -
## ----------------------------------------------------------------------------

## ----------------------------------------------------------------------------
## Configuration --------------------------------------------------------------

  MOD		=	`pwd | rev | cut -d "/" -f3 | rev`

  BIN		=	`pwd | rev | cut -d "/" -f1 | rev`
  FLAG		=	-W -Wall  -g -g3 -ggdb -fpermissive

  INCLUDE	=	-I./include/ -I../../include/
  SRC		=	$(wildcard src/*.cpp)
  OBJ		=	$(SRC:.cpp=.o)
  LIBPATH	=	-L../../
  LIB		=	-llapin -lsfml-graphics -lsfml-audio -lsfml-window	\
			-lsfml-system -lstdc++ -lm -ldl -lpthread

  ## Rules ------------------------------------------------------------------
  all:		bin
  bin:		$(OBJ)
		@g++ $(OBJ) -o $(BIN) $(LIBPATH) $(LIB)
		@echo "[OUT] " $(BIN)
		@echo $(BIN) | tr '[:lower:]' '[:upper:]'
  .cpp.o:
		@g++ $(INCLUDE) $(FLAG) -c $< -o $@
		@echo "[GCC]" $<
  clean:
		@rm -f $(OBJ)
  fclean:	clean
		@rm -f $(BIN)
  re:		fclean all

## ----------------------------------------------------------------------------
## MISC -----------------------------------------------------------------------

  .PHONY: all clean fclean re

  .SUFFIXES: .cpp .o
