# TORCS Racing Bot
TORCS (The Open Racing Simulator) is a cross platform open source 3D car racing simulator. TORCS Racing Bot uses a Behaviour Tree for its programmed AI drivers.

## Introduction
TORCS Racing Bot uses a modified driver found in the *torcs robot tutorial* with some other improvements from the *bt* robot from within inside the TORCS project. The modified driver is built to interact with a Behaviour Tree to control its driving behaviour.

## Why a Behaviour Tree.
This section outlines the reasons for using a Behaviour Tree to control the robot cars behaviour as opposed to using other approaches.  
* Behaviour Trees increase Cyclomatic complexity linearly whereas Finite State Machines increase Cyclomatic complexity super-linearly.
* Behaviour Trees grow by an order of O(n) whereas Finite State Machines grow by an order O(n2).
* The Cyclomatic complexity of a Behaviour Tree implementation is a lot less than the Cyclomatic complexity of a Finite State Machine implementation, despite them implementing the same behaviour.
* The Maintainability index of a Behaviour Tree does not increase when more functionality is added, compared to a Finite State Machine implementation where the Maintainability index increases has more functionality is added.
More about this can be read in the *Behaviour Tress for decision-making in autonomous driving* paper below.  

## Improvements
This section outlines possible improvements to the TORCS Racing Bot project.

## Bibliography
* Magnus Olson, MO. (2016) *Behaviour Tress for decision-making in autonomous driving*. Available at: [Link](http://www.diva-portal.org/smash/get/diva2:907048/FULLTEXT01.pdf). Accessed on: (03/12/2018).
* Bernhard Wymann, BW. TORCS Robot Tutorial (2018). *"torcs robot tutorial"*. Available at: [Link](http://www.berniw.org/tutorials/robot/tutorial.html). Accessed on: (19/11/2018).
* Champandard, Dunston, AC, PD. (2016) *The Behaviour Tree Starter Kit*. Available at: [Link](http://www.gameaipro.com/GameAIPro/GameAIPro_Chapter06_The_Behavior_Tree_Starter_Kit.pdf). Accessed on: (19/11/2018).
