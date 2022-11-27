The simplest algorithm that we can use to solve this problem is the following.

Initially we define a random route. After that we search for new routes by swapping 2 random cities in the defined route. When the new route is shorter we keep it and we repeat the process. If the new route is not shorter we bring back the two cities in their previus position and we search for a new random pair of cities.
