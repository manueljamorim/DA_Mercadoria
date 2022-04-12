#include "Task2.h"

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

	env.out() << "Solution: " << cplex.getStatus() << endl;
	env.out() << "Profit: " << cplex.getObjValue() << endl;

}