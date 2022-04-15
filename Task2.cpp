#include "Task2.h"


void Task2::test_1() {
	data.carrinhas.push_back({ 5, 6, 10, 1 });
	data.carrinhas.push_back({ 5, 6, 12, 2 });

	data.encomendas.push_back({ 1, 1, 3, 1, 1 });
	data.encomendas.push_back({ 2, 3, 8, 1, 2 });
	data.encomendas.push_back({ 3, 1, 6, 1, 3 });
	data.encomendas.push_back({ 2, 2, 4, 1, 4 });
	data.encomendas.push_back({ 4, 3, 10, 1, 5 });

	print_entry_data();
	solve();
	// resultado ótimo pra este exemplo é 5
	//  encomenda 1, 2 e 4 pra carrinha 1
	//      (3 + 8 + 4) - 10 = 5
	//  ou encomenda 2 e 3 pra carrinha 1 e encomenda 1 e 5 pra carrinha 2
	//      ((8 + 6) - 10) + ((10 + 3) - 12) = 5
}

void Task2::test_2() {
	data.carrinhas.push_back({ 5, 6, 12, 1 });

	data.encomendas.push_back({ 3, 1, 6, 1, 1 });
	data.encomendas.push_back({ 2, 2, 4, 1, 2 });

	print_entry_data();
	solve();
	// resultado ótimo pra este exemplo é 0
	// o algoritmo não permite lucro negativo
}

void Task2::test_random(LoadData dataset) {
	// Pick between 1 to 15 workers from the dataset
	int n = 1 + (rand() % 15);
	vector<int> nums;
	for (int i = 0; i < n; i++) {
		int choice = rand() % dataset.carrinhas.size();
		if (count(nums.begin(), nums.end(), choice)) { // To ensure the same worker isn't picked
			i--;
			continue;
		}
		data.carrinhas.push_back(dataset.carrinhas.at(choice));
		nums.push_back(choice);
	}

	nums.clear();

	// Pick between 1 to 100 packages from the dataset
	n = 1 + (rand() % 100);
	for (int i = 0; i < n; i++) {
		int choice = rand() % dataset.encomendas.size();
		if (count(nums.begin(), nums.end(), choice)) {  // To ensure the same package isn't picked
			i--;
			continue;
		}
		data.encomendas.push_back(dataset.encomendas.at(choice));
		nums.push_back(choice);
	}

	print_entry_data();
	solve();
}

void Task2::test_original(LoadData& dataset) {
	data.carrinhas = dataset.carrinhas;
	data.encomendas = dataset.encomendas;

	solve();
}

void Task2::print_entry_data() {
	cout << setfill('=') << setw(20) << "" << "Entry data" << setw(20) << "" << endl;
	cout << right << setfill(' ') << setw(20) << "pesoMax" << setw(10) << "volMax" << setw(10) << "custo" << endl;
	for (int i = 0; i < data.carrinhas.size(); i++)
		cout << setfill(' ') << "Estafeta " << left << setw(2) << data.carrinhas[i].id_c <<
		right << setw(8) << data.carrinhas[i].volMax << setw(10) << data.carrinhas[i].pesoMax << setw(11) << data.carrinhas[i].custo << endl;

	cout << endl << right << setfill(' ') << setw(20) << "peso" << setw(10) << "volume" << setw(15) << "recompensa" << endl;
	for (int i = 0; i < data.encomendas.size(); i++) {
		cout << "Encomenda " << left << setw(3) << data.encomendas[i].id_e <<
			right << setw(6) << data.encomendas[i].volume << setw(10) << data.encomendas[i].peso << setw(11) << data.encomendas[i].recompensa << endl;
	}

	cout << endl;
	cout << "Total estafetas: " << setw(4) << data.carrinhas.size() << endl;
	cout << "Total encomendas: " << setw(3) << data.encomendas.size() << endl,
	cout << setfill('=') << setw(50) << "" << endl;
}

int Task2::solve() {

	// Setting up the model and environment
	IloEnv env;
	IloModel model(env);


	// Declaring n and m
	unsigned long int n = data.carrinhas.size();	// = number of workers (estafetas)
	unsigned long int m = data.encomendas.size();	// = number of packages (encomendas)

	// Declaring decision variable y[e]
	IloNumVarArray y(env);
	for (int e = 0; e < n; e++) {
		string number = "y:" + to_string(e);
		char* char_array = (char*)malloc((number.size() + 1) * sizeof(char));
		strcpy(char_array, number.c_str());

		// ILOBOOL to indicate that it's a boolean/binary variable, thus only being either 0 or 1 
		y.add(IloNumVar(env, 0, 1, ILOBOOL, char_array));
	}

	// Declaring decision variable x[e][p]
	// Two loops as for each worker (estafeta) 'e', we can have 'p' packages (encomendas)
	IloArray<IloNumVarArray> x(env);
	for (int e = 0; e < n; e++) {
		IloNumVarArray line(env);

		for (int p = 0; p < m; p++) {
			string number2 = "x:" + to_string(e) + "," + to_string(p);
			char* char_array2 = (char*)malloc((number2.size() + 1) * sizeof(char));
			strcpy(char_array2, number2.c_str());

			// ILOBOOL to indicate that it's a boolean/binary variable, thus only being either 0 or 1 
			line.add(IloNumVar(env, 0, 1, ILOBOOL, char_array2));
		}
		x.add(line);
	}


	// Constraints
	for (int p = 0; p < m; p++) {
		IloExpr con(env);
		for (int e = 0; e < n; e++) {
			con += x[e][p];
		}
		model.add(con <= 1);
	}
	
	for (int e = 0; e < n; e++) {
		IloExpr con(env);
		for (int p = 0; p < m; p++) {
			con += x[e][p] * data.encomendas[p].peso;
		}
		model.add(con <= data.carrinhas[e].pesoMax * y[e]);
	}

	for (int e = 0; e < n; e++) {
		IloExpr con(env);
		for (int p = 0; p < m; p++) {
			con += x[e][p] * data.encomendas[p].volume;
		}
		model.add(con <= data.carrinhas[e].volMax * y[e]);
	}


	// Objective function
	IloExpr obj(env);
	for (int e = 0; e < n; e++) {
		for (int p = 0; p < m; p++) {
			obj += data.encomendas[p].recompensa * x[e][p];
		}
		obj -= data.carrinhas[e].custo * y[e];
	}

	model.add(IloMaximize(env, obj));


	// Applying the solver
	IloCplex cplex(model);
	cplex.setOut(env.getNullStream());

	if (!cplex.solve()) {
		env.error() << "Failed to optimize LP" << endl;
		throw(-1);
	}

	cout << endl << setfill('=') << setw(21) << "" << "Out data" << setw(21) << "" << endl;
 	env.out() << "Solution: " << cplex.getStatus() << endl;
	env.out() << "Profit: " << cplex.getObjValue() << endl;
	cout << setfill('=') << setw(50) << "" << endl;
}
