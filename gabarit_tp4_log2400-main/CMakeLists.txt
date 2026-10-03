cmake_minimum_required(VERSION 3.15)

project(TonYogourt)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include) 

file(GLOB_RECURSE SOURCES src/*.cpp)

add_executable(TonYogourt ${SOURCES}
        include/Singleton/Application.h
        src/Singleton/Application.cpp
        include/State/Commande.h
        src/State/Commande.cpp
        include/Strategy/ModePaiement.h
        include/State/CommandeState.h
        include/Strategy/ModeEclair.h
        include/Strategy/ModePrev.h
        include/Strategy/ModePoly.h
        src/Strategy/ModePoly.cpp
        src/Strategy/ModePrev.cpp
        src/Strategy/ModeEclair.cpp
        include/DecoratorAndPrototype/Yogourt.h
        include/DecoratorAndPrototype/Garniture.h
        include/DecoratorAndPrototype/YogourtGrec.h
        include/DecoratorAndPrototype/YogourtNature.h
        include/DecoratorAndPrototype/GarnitureFruits.h
        include/DecoratorAndPrototype/GarnitureMiel.h
        include/DecoratorAndPrototype/GarnitureChocolat.h
        include/DecoratorAndPrototype/GarnitureGranola.h
        include/State/InitialState.h
        include/State/PreparationState.h
        include/State/TerminerState.h
        include/Factory/YogourtFactory.h
        src/State/InitialState.cpp
        src/State/PreparationState.cpp
        src/State/TerminerState.cpp
        src/Factory/YogourtFactory.cpp
        src/DecoratorAndPrototype/YogourtGrec.cpp
        src/DecoratorAndPrototype/YogourtNature.cpp
        include/Miscellaneous/StockManager.h
        src/Miscellaneous/StockManager.cpp
        src/DecoratorAndPrototype/GarnitureMiel.cpp
        src/DecoratorAndPrototype/GarnitureGranola.cpp
        src/DecoratorAndPrototype/GarnitureChocolat.cpp
        src/DecoratorAndPrototype/GarnitureFruits.cpp
        include/Command/CommandManager.h
        include/Command/Command.h
        include/Command/AjouterGarnitureCommand.h
        src/Command/CommandManager.cpp
        src/Command/AjouterGarnitureCommand.cpp
        include/Observer/Subscriber.h
        include/Miscellaneous/WARNING.h
 "include/ui/UIController.h" "src/ui/UIController.cpp")
