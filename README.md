
# Proj'ISEN - CIR2 - Projet de fin d'année

Dépot GIT lié au développement de notre robot cartographieur : MAP-MATE !

Pour cela nous avons divisé le projet en 3 parties majeures : 

- Configuration Raspberry PI 4B
- Code controle du robot
- Application mobile





## Configuration Raspberry PI 4B

Pour la configuration de notre carte, nous avons utilisé Ubuntu 22.04 pour éxécuter l'ensemble des lignes de commande nécessaire afin d'installer ROS 2, et pouvoir utilisé le logiciel RVIZ qui nous donne une visions 2D des points renvoyés par notre capteur LiDAR.
## Code controle du robot

Pour controler les moteurs de notre robot, nous avons utilisé une carte Arduino Nano et avons développé un code Arduino car ce dernier se rapproche de la synthaxe du C que nous connaissions déja.
## Application mobile

Pour piloter notre robot, nous avons utilisé une application mobile couplée à un module Bluetooth permettant l'échange de données et la communication entre la tablette Android que nous avons utilisé et le notre code Arduino.

L'application a été designée sur MIT App Inventor 2 en ligne. L'avantage de ce site est qu'il est facile de récupéré l'application sur tablette en scannant un QR code. De plus l'aspect visuel est facile à développer même si nous ne sommes pas des artistes.

Enfin, cette application permet très facilement de relié chaque bloc à une instruction grâce à une programmation par bloc.
