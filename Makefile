CC = clang++

CFLAGS = -std=c++11 -Weverything -Wno-switch -Wno-switch-enum -Wno-c++98-compat -Werror -Wno-padded -Wno-global-constructors -Wno-exit-time-destructors -Wno-implicit-fallthrough -ferror-limit=0 
DEPS = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

OBJS = \
	   build/main.o \
	   build/MusicFactory.o \
	   build/ControllerFactory.o \
	   build/CellFactory.o \
	   build/Context.o \
	   build/Controller.o \
	   build/DirReader.o \
	   build/FileWriter.o \
	   build/StringsListsUtils.o \
	   build/CellsUtils.o \
	   build/CellsFilter.o \
	   build/Messages.o \
	   build/Directories.o \
	   build/Extensions.o \
	   build/Fonts.o \
	   build/Sounds.o \
	   build/Colors.o \
	   build/Screens.o \
	   build/Window.o \
	   build/Dimensions.o \
	   build/Positions.o \
	   build/Serie.o \
	   build/ButtonWidget.o \
	   build/CursorWidget.o \
	   build/InputTextWidget.o \
	   build/ItemsListWidget.o \
	   build/OrderedItemsListWidget.o \
	   build/TitleBarWidget.o \
	   build/CellSelectorWidget.o \
	   build/FrameWidget.o \
	   build/Widget.o \
	   build/MainMenuController.o \
	   build/NewGameController.o \
	   build/EditorMenuController.o \
	   build/EditorLevelController.o \
	   build/EditorSerieController.o \
	   build/OpenSerieController.o \
	   build/OpenLevelController.o \
	   build/GameController.o \
	   build/Level.o \
	   build/Cell.o \
	   build/EmptyCell.o \
	   build/DepartureCell.o \
	   build/ArrivalCell.o \
	   build/StarCell.o \
	   build/LifeCell.o \
	   build/DamageCell.o \
	   build/MoreTimeCell.o \
	   build/LessTimeCell.o \
	   build/FloorUpCell.o \
	   build/FloorDownCell.o \
	   build/WallCell.o \
	   build/ElevatorUpCell.o \
	   build/ElevatorDownCell.o \
	   build/QuarterLeftRotateCell.o \
	   build/QuarterRightRotateCell.o \
	   build/QuarterHalfRotateCell.o \
	   build/VerticalMirrorCell.o \
	   build/HorizontalMirrorCell.o \
	   build/HasMenuSelectorAnimation.o \
	   build/HiddenCellPicture.o

INC = -I includes

$(shell mkdir build)

all: $(OBJS)
	$(CC) $(OBJS) -o bin/Memoris $(DEPS)

build/main.o: src/main.cpp
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

# utils

build/MusicFactory.o: src/MusicFactory.cpp
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

build/ControllerFactory.o: src/ControllerFactory.cpp
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

build/CellFactory.o: src/CellFactory.cpp
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

build/Context.o: src/Context.cpp
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

build/Controller.o: src/Controller.cpp
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

build/DirReader.o: src/DirReader.cpp
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

build/FileWriter.o: src/FileWriter.cpp
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

build/StringsListsUtils.o: src/StringsListsUtils.cpp
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

build/CellsUtils.o: src/CellsUtils.cpp
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

build/CellsFilter.o: src/CellsFilter.cpp
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

build/HiddenCellPicture.o: src/HiddenCellPicture.cpp
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

# defines

build/Colors.o: src/Colors.cpp
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

build/Window.o: src/Window.cpp
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

build/Dimensions.o: src/Dimensions.cpp
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

build/Positions.o: src/Positions.cpp
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

build/Directories.o: src/Directories.cpp
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

build/Extensions.o: src/Extensions.cpp
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

build/Fonts.o: src/Fonts.cpp
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

build/Sounds.o: src/Sounds.cpp
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

build/Screens.o: src/Screens.cpp
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

build/Messages.o: src/Messages.cpp
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

# entities

build/Serie.o: src/Serie.cpp
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

build/Level.o: src/Level.cpp
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

build/Cell.o: src/Cell.cpp
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

build/EmptyCell.o: src/EmptyCell.cpp
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

build/DepartureCell.o: src/DepartureCell.cpp
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

build/ArrivalCell.o: src/ArrivalCell.cpp
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

build/StarCell.o: src/StarCell.cpp
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

build/LifeCell.o: src/LifeCell.cpp
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

build/DamageCell.o: src/DamageCell.cpp
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

build/MoreTimeCell.o: src/MoreTimeCell.cpp
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

build/LessTimeCell.o: src/LessTimeCell.cpp
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

build/FloorUpCell.o: src/FloorUpCell.cpp
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

build/FloorDownCell.o: src/FloorDownCell.cpp
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

build/ElevatorUpCell.o: src/ElevatorUpCell.cpp
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

build/ElevatorDownCell.o: src/ElevatorDownCell.cpp
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

build/WallCell.o: src/WallCell.cpp
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

build/QuarterLeftRotateCell.o: src/QuarterLeftRotateCell.cpp
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

build/QuarterRightRotateCell.o: src/QuarterRightRotateCell.cpp
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

build/QuarterHalfRotateCell.o: src/QuarterHalfRotateCell.cpp
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

build/VerticalMirrorCell.o: src/VerticalMirrorCell.cpp
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

build/HorizontalMirrorCell.o: src/HorizontalMirrorCell.cpp
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

# widgets

build/ButtonWidget.o: src/ButtonWidget.cpp
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

build/CursorWidget.o: src/CursorWidget.cpp
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

build/InputTextWidget.o: src/InputTextWidget.cpp
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

build/ItemsListWidget.o: src/ItemsListWidget.cpp
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

build/OrderedItemsListWidget.o: src/OrderedItemsListWidget.cpp
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

build/TitleBarWidget.o: src/TitleBarWidget.cpp
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

build/CellSelectorWidget.o: src/CellSelectorWidget.cpp
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

build/FrameWidget.o: src/FrameWidget.cpp
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

build/Widget.o: src/Widget.cpp
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

# controllers

build/MainMenuController.o: src/MainMenuController.cpp
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

build/NewGameController.o: src/NewGameController.cpp
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

build/EditorMenuController.o: src/EditorMenuController.cpp
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

build/EditorLevelController.o: src/EditorLevelController.cpp
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

build/EditorSerieController.o: src/EditorSerieController.cpp
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

build/OpenSerieController.o: src/OpenSerieController.cpp
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

build/OpenLevelController.o: src/OpenLevelController.cpp
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

build/GameController.o: src/GameController.cpp
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

# policies

build/HasMenuSelectorAnimation.o: src/HasMenuSelectorAnimation.cpp
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<
