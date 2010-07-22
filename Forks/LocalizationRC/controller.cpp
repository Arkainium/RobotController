#include "definitions.h"
#include "robot.h"
#include "loiter.h"

#include "libplayerc++/playerc++.h"
using namespace PlayerCc;

#include <cstdlib>
#include <iostream>
#include <sstream>
using namespace std;

int main(int argc, char **argv)
{
	// ensure that the program was run properly
	if (argc < 3 || argc > 5) {
		cerr << "program usage: " << argv[0]
		     << " <server_port> <server_hostname>"
		     << " [player_port] [player_hostname]" << endl;
		exit(1);
	}

	// initialize default arguments
	int server_port = -1;
	string server_hostname;
	int player_port = 6665;
	string player_hostname = "localhost";

	// retrieve command line arguments
	int current_arg = 0;
	++current_arg; // skip the program name

	// get the server port
	if (argc >= current_arg+1) {
		stringstream ss(argv[current_arg]);
		if (!(ss >> server_port) || server_port <= 0) {
			cerr << "invalid argument: server_port" << endl;
			cerr << "program usage: " << argv[0]
			     << " <server_port> <server_hostname>"
			     << " [player_port] [player_hostname]" << endl;
			exit(1);
		}
		++current_arg;
	}

	// get the server hostname
	if (argc >= current_arg+1) {
		stringstream ss(argv[current_arg]);
		if (!(ss >> server_hostname)) {
			cerr << "invalid argument: server_hostname" << endl;
			cerr << "program usage: " << argv[0]
			     << " <server_port> <server_hostname>"
			     << " [player_port] [player_hostname]" << endl;
			exit(1);
		}
		++current_arg;
	}

	// get the player port
	if (argc >= current_arg+1) {
		stringstream ss(argv[current_arg]);
		if (!(ss >> player_port) || player_port <= 0) {
			cerr << "invalid argument: player_port" << endl;
			cerr << "program usage: " << argv[0]
			     << " <server_port> <server_hostname>"
			     << " [player_port] [player_hostname]" << endl;
			exit(1);
		}
		++current_arg;
	}

	// get the player host
	if (argc >= current_arg+1) {
		stringstream ss(argv[current_arg]);
		if (!(ss >> player_hostname)) {
			cerr << "invalid argument: player_hostname" << endl;
			cerr << "program usage: " << argv[0]
			     << " <server_port> <server_hostname>"
			     << " [player_port] [player_hostname]" << endl;
			exit(1);
		}
		++current_arg;
	}

	try {
		// connect to the player server
		PlayerClient pc(player_hostname, player_port);

		// startup the robot
		Robot robot(pc);

		// connect robot to the central server
		if (!robot.Connect(server_hostname, server_port)) {
			cerr << "Failed to establish a connection to the Central Server.\n"
			     << "Central Server hostname: " << server_hostname << "\n"
			     << "Central Server port: " << server_port << endl;
			exit(1);
		}

		// select a behavior
		Loiter behavior(pc);
		//robot.SetBehavior(&behavior);

		// enter main loop
		while (robot.GetState() != STATE_QUIT) {
			// Update Player interfaces.
			pc.ReadIfWaiting();

			// Update the robot.
			robot.Update();

			// Take a quick breath.
			usleep(1);
		}

	} catch (PlayerError) {
		cerr << "Failed to establish a connection to the Player Server.\n"
		     << "Player Server hostname: " << player_hostname << "\n"
		     << "Player Server port: " << player_port << endl;
		exit(1);
	}

	return 0;
}
