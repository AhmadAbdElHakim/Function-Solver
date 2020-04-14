#include <iostream>
#include <string>
#include <cstdlib>
#define SIZE 25

using namespace std;
class LTerm
{
private:
	float coeff;
	string var;
public:
	void setLTerm(float c, string v)
	{
		coeff = c;
		var = v;
	}
	void setVar(string v) { var = v; }
	void setCoeff(float c) { coeff = c; }
	float getCoeff() { return coeff; }
	string getVar() { return var; }
	int countOperators(string s)
	{
		int count = 0;
		for (int i = 0; i < s.length(); i++)
			if (s[i] == '+' || s[i] == '-' || s[i] == '=')
				count++;
		return count;
	}
};
class RTerm
{
private:
	float coeff;
	string var;
public:
	void setRTerm(float c, string v)
	{
		coeff = c;
		var = v;
	}
	void setVar(string v) { var = v; }
	void setCoeff(float c) { coeff = c; }
	float getCoeff() { return coeff; }
	string getVar() { return var; }
	int rCountOperators(string s)
	{
		int end = s.rfind('='), count = 0;
		for (int i = end; i < s.length(); i++)
			if (s[i] == '+' || s[i] == '-' || s[i] == '=')
				count++;
		return count;
	}
};
int countOperators(string s);
int rCountOperators(string s);
int main()
{
	int n, i, c = 0, r = 1, no = 0, gTransTerm[100], gtransConst[100], gsimTerm[100], opSum = 0, count = 0, addf = 0, adds = 0, subf = 0, subs = 0, subtf = 0, subts = 0, fc = 0, sc = 0, tem, myFlag = 0, swap = 0;
	string eq[100], lTerm[100][SIZE], rTerm[100][SIZE], ALTV[100][SIZE], ALTC[100][SIZE], ARTV[100][SIZE], ARTC[100][SIZE], TCS[100][SIZE], operation, var[500], column, sAdd, sSub, variable, fcs, scs, CS[2][SIZE], vars[SIZE], cram, cramS[100][SIZE];
	float ALTFC[100][SIZE], ARTFC[100][SIZE], gsum[100], C[100][SIZE], cTemp[SIZE], det = 1, S[SIZE] = { 0 }, sol[SIZE] = { 0 }, so[SIZE] = { 0 }, dsum[100];
	LTerm T[100][SIZE], add, sub, ST[2][SIZE], DT[100][SIZE], D[100][SIZE];
	RTerm FT[50][SIZE];
	cin >> n;
	for (i = 0; i < n; i++)
		cin >> eq[i];
	for (i = 0; i < n; i++)
	{
		int LT = 0, RT = 0, index = 0, nextIndex, end, lTermVarIndex, lTermEndVarIndex, rTermVarIndex, rTermEndVarIndex, TransTerm = 0, transConst = 0, simTerm = 0, sum = 0;
		string firstTerm, rFirstTerm;
		end = eq[i].rfind('=');
		lTermVarIndex = lTerm[i][LT].find_first_of("_abcdefghijklmnopqrstuvwxyzABCDEFGHYJKLMNOPQRSTUVWXYZ");
		rTermVarIndex = lTerm[i][LT].find_first_of("_abcdefghijklmnopqrstuvwxyzABCDEFGHYJKLMNOPQRSTUVWXYZ", end);
		while (index < end)
		{
			nextIndex = eq[i].find_first_of("+-=", index + 1);
			lTerm[i][LT] = eq[i].substr(index, nextIndex - index);
			if (lTerm[i][LT].find_first_of("+=") != -1)
				lTerm[i][LT] = eq[i].substr(index + 1, nextIndex - index - 1);
			if (lTerm[i][LT] == "")
				lTerm[i][LT] = '-' + lTerm[i][LT];
			index = nextIndex;
			lTermVarIndex = lTerm[i][LT].find_first_of("_abcdefghijklmnopqrstuvwxyzABCDEFGHYJKLMNOPQRSTUVWXYZ");
			lTermEndVarIndex = lTerm[i][LT].find_first_of("+-=", lTermVarIndex + 1);
			ALTC[i][LT] = lTerm[i][LT].substr(0, lTermVarIndex);
			ALTFC[i][LT] = atof(ALTC[i][LT].c_str());
			if (ALTFC[i][LT] == 0 && lTerm[i][LT].find('-') == -1 && lTerm[i][LT] != "0")
				ALTFC[i][LT] = 1;
			if (ALTFC[i][LT] == 0 && lTerm[i][LT].find('-') != -1 && lTerm[i][LT] != "0")
				ALTFC[i][LT] = -1;
			if (lTermVarIndex == -1)
				ALTV[i][LT] = "";
			else
				ALTV[i][LT] = lTerm[i][LT].substr(lTermVarIndex, lTermEndVarIndex);
			if (ALTV[i][LT] == "")
			{
				FT[i][rCountOperators(eq[i]) - 1 + transConst].setRTerm(-ALTFC[i][LT], "");
				ALTFC[i][LT] = 0;
				transConst++;
			}
			if (lTerm[i][0].find('-') != -1)
				simTerm = 1;
			T[i][LT].setLTerm(ALTFC[i][LT], ALTV[i][LT]);
			LT++;
		}
		while (end <= eq[i].length())
		{
			nextIndex = eq[i].find_first_of("+-=", end + 1);
			rTerm[i][RT] = eq[i].substr(end, nextIndex - end);
			if (rTerm[i][RT].find_first_of("+=") != -1)
				rTerm[i][RT] = eq[i].substr(end + 1, nextIndex - end - 1);
			if (rTerm[i][RT] == "")
				rTerm[i][RT] = '-' + rTerm[i][RT];
			end = nextIndex;
			rTermVarIndex = rTerm[i][RT].find_first_of("_abcdefghijklmnopqrstuvwxyzABCDEFGHYJKLMNOPQRSTUVWXYZ");
			rTermEndVarIndex = rTerm[i][RT].find_first_of("+-=", rTermVarIndex + 1);
			ARTC[i][RT] = rTerm[i][RT].substr(0, rTermVarIndex);
			ARTFC[i][RT] = atof(ARTC[i][RT].c_str());
			if (ARTFC[i][RT] == 0 && rTerm[i][RT].find('-') == -1 && rTerm[i][RT] != "0")
				ARTFC[i][RT] = 1;
			if (ARTFC[i][RT] == 0 && rTerm[i][RT].find('-') != -1 && rTerm[i][RT] != "0")
				ARTFC[i][RT] = -1;
			if (rTermVarIndex == -1)
				ARTV[i][RT] = "";
			else
				ARTV[i][RT] = rTerm[i][RT].substr(rTermVarIndex, rTermEndVarIndex);
			if (ARTV[i][RT] != "")
			{
				T[i][countOperators(eq[i]) + TransTerm].setLTerm(-ARTFC[i][RT], ARTV[i][RT]);
				ARTFC[i][RT] = 0;
				ARTV[i][RT] = "";
				TransTerm++;
			}
			if (rTerm[i][0].find('-') != -1)
				sum = 1;
			FT[i][RT].setRTerm(ARTFC[i][RT], ARTV[i][RT]);
			RT++;
		}
		for (int I = 0; I < countOperators(eq[i]); I++)
		{
			for (int J = I + 1; J < countOperators(eq[i]); J++)
			{
				if (T[i][J].getVar() < T[i][I].getVar())
				{
					string tempV = T[i][I].getVar();
					float tempC = T[i][I].getCoeff();
					T[i][I].setVar(T[i][J].getVar());
					T[i][I].setCoeff(T[i][J].getCoeff());
					T[i][J].setVar(tempV);
					T[i][J].setCoeff(tempC);
				}
			}
		}
		for (int I = 0; I < countOperators(eq[i]) + TransTerm; I++)
		{
			for (int J = 1; J < countOperators(eq[i]) + TransTerm; J++)
			{
				if (T[i][I].getVar() == T[i][J].getVar() && I != J)
				{
					T[i][I].setCoeff(T[i][I].getCoeff() + T[i][J].getCoeff());
					T[i][J].setLTerm(0, "");
				}
			}
		}
		for (int I = 0; I < countOperators(eq[i]) + TransTerm; I++)
		{
			for (int J = I + 1; J < countOperators(eq[i]) + TransTerm; J++)
			{
				if (T[i][J].getVar() < T[i][I].getVar())
				{
					string tempV = T[i][I].getVar();
					float tempC = T[i][I].getCoeff();
					T[i][I].setVar(T[i][J].getVar());
					T[i][I].setCoeff(T[i][J].getCoeff());
					T[i][J].setVar(tempV);
					T[i][J].setCoeff(tempC);
				}
			}
		}
		for (int I = 0; I < countOperators(eq[i]) + TransTerm; I++)
			if (T[i][I].getCoeff() == 0 && T[i][I].getVar() == "")
				simTerm++;
		for (int I = 0; I < rCountOperators(eq[i]) + transConst - 1; I++)
			sum = sum + FT[i][I].getCoeff();
		for (int I = simTerm; I < countOperators(eq[i]) + TransTerm; I++)
			TCS[i][I] = to_string(T[i][I].getCoeff());
		gTransTerm[i] = TransTerm;
		gtransConst[i] = transConst;
		gsimTerm[i] = simTerm;
		gsum[i] = sum;
		dsum[i] = sum;
	}
	for (int i = 0; i < n; i++)
	{
		for (int I = 0; I < countOperators(eq[i]) + gTransTerm[i]; I++)
		{
			if (T[i][I].getVar() != "")
				var[I + opSum] = T[i][I].getVar();
		}
		opSum = opSum + countOperators(eq[i]) + 3;
	}
	for (int I = 0; I < opSum; I++)
	{
		for (int J = 1; J < opSum; J++)
			if (var[I] == var[J] && I != J)
				var[J] = "";
	}
	for (int y = 0; y < opSum; y++)
	{
		if (var[y] != "")
		{
			vars[c] = var[y];
			count++;
			c++;
		}
	}
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < count; j++)
			DT[i][j].setLTerm(0, vars[j]);
	}
	for (int i = 0; i < n; i++)
	{
		for (int I = 0; I < count + 1; I++)
		{
			for (int J = gsimTerm[i]; J < count + gsimTerm[i]; J++)
			{
				if (DT[i][I].getVar() == T[i][J].getVar() && T[i][J].getVar() != "")
				{
					DT[i][I].setLTerm(T[i][J].getCoeff(), T[i][J].getVar());
					break;
				}
			}
		}
	}
	for (int j = 0; j< count; j++)
	{
		for (int i = 0; i < n; i++)
			D[j][i].setLTerm(DT[i][j].getCoeff(), DT[i][j].getVar());
	}
	for (int i = 0; i < n; i++)
	{
		for (int M = 0; M < count; M++)
		{
			C[i][M] = D[M][i].getCoeff();
			cramS[i][M] = to_string(C[i][M]);
		}
	}
	for (int N = 0; N < count; N++)
	{
		if (C[N][N] == 0)
		{
			for (int x = 0; x < count; x++)
			{
				cTemp[x] = C[N][x];
				C[N][x] = C[N + 1][x];
				C[N + 1][x] = cTemp[x];
			}
			float sumTemp = dsum[N];
			dsum[N] = dsum[N + 1];
			dsum[N + 1] = sumTemp;
			swap++;
			N--;
		}
		else
		{
			for (int i = 0; i < n - N; i++)
			{
				float factor = -(C[N + i + 1][N] / C[N][N]);
				for (int M = 0; M < count; M++)
				{
					C[N + i + 1][M] = (factor * C[N][M]) + C[N + i + 1][M];
					cramS[N + i + 1][M] = to_string(C[N + i + 1][M]);
				}
				dsum[N + i + 1] = (factor * dsum[N]) + dsum[N + i + 1];
			}
		}
	}
	getline(cin >> ws, operation);
	while (operation != "quit")
	{
		if (operation == "num_vars")
			cout << count << endl;
		else if (operation.substr(0, 8) == "equation")
		{
			if (operation.length() == 11)
				no = (((int)operation[9] - 48) * 10) + ((int)operation[10] - 48) - 1;
			else if (operation.length() == 10)
				no = (int)operation[9] - 49;
			else if (operation.length() == 12)
				no = 100;
			if (no >= n)
				break;
			for (int I = gsimTerm[no]; I < countOperators(eq[no]) + gTransTerm[no]; I++)
			{
				if (TCS[no][I].find('-') == -1 && I != gsimTerm[no])
					cout << "+" << T[no][I].getCoeff() << T[no][I].getVar();
				else
					cout << T[no][I].getCoeff() << T[no][I].getVar();
			}
			cout << "=" << gsum[no] << endl;
		}
		else if (operation.substr(0, 6) == "column")
		{
			column = operation.substr(7);
			for (int i = 0; i < n; i++)
			{
				for (int I = gsimTerm[i]; I < countOperators(eq[i]) + gTransTerm[i]; I++)
				{
					if (column == T[i][I].getVar())
						cout << T[i][I].getCoeff() << endl;
					else if (eq[i].find(column) == -1)
					{
						cout << "0" << endl;
						break;
					}
				}
			}
		}
		else if (operation.substr(0, 3) == "add")
		{
			if (operation.length() == 9)
			{
				addf = (((int)operation[4] - 48) * 10) + ((int)operation[5] - 48) - 1;
				adds = (((int)operation[7] - 48) * 10) + ((int)operation[8] - 48) - 1;
			}
			else if (operation.length() == 8)
			{
				if (operation[5] == ' ')
				{
					addf = (int)operation[4] - 49;
					adds = (((int)operation[6] - 48) * 10) + ((int)operation[7] - 48) - 1;
				}
				else if (operation[6] == ' ')
				{
					addf = (((int)operation[4] - 48) * 10) + ((int)operation[5] - 48) - 1;
					adds = (int)operation[7] - 49;
				}
			}
			else if (operation.length() == 7)
			{
				addf = (int)operation[4] - 49;
				adds = (int)operation[6] - 49;
			}
			else
				break;
			if (addf >= n || adds >= n)
				break;
			int I = gsimTerm[addf];
			for (int J = gsimTerm[adds]; J < countOperators(eq[adds]) + gTransTerm[adds]; J++)
			{
				if (T[addf][I].getVar() == T[adds][J].getVar())
				{
					add.setLTerm(T[addf][I].getCoeff() + T[adds][J].getCoeff(), T[addf][I].getVar());
					sAdd = to_string(add.getCoeff());
					if (sAdd.find('-') == -1 && I != gsimTerm[addf])
						cout << "+" << add.getCoeff() << add.getVar();
					else
						cout << add.getCoeff() << add.getVar();
				}
				if (eq[addf].find(T[adds][J].getVar()) == -1)
				{
					if (TCS[adds][J].find('-') == -1)
						cout << "+" << T[adds][J].getCoeff() << T[adds][J].getVar();
					else
						cout << T[adds][J].getCoeff() << T[adds][J].getVar();
					I--;
				}
				if (eq[adds].find(T[addf][I].getVar()) == -1)
				{
					if (TCS[addf][I].find('-') == -1)
						cout << "+" << T[addf][I].getCoeff() << T[addf][I].getVar();
					else
						cout << T[addf][I].getCoeff() << T[addf][I].getVar();
					I++;
				}
				I++;
			}
			cout << "=" << gsum[addf] + gsum[adds] << endl;
		}
		else if (operation.substr(0, 8) == "subtract")
		{
			if (operation.length() == 14)
			{
				subf = (((int)operation[9] - 48) * 10) + ((int)operation[10] - 48) - 1;
				subs = (((int)operation[12] - 48) * 10) + ((int)operation[13] - 48) - 1;
			}
			else if (operation.length() == 13)
			{
				if (operation[10] == ' ')
				{
					subf = (int)operation[9] - 49;
					subs = (((int)operation[11] - 48) * 10) + ((int)operation[12] - 48) - 1;
				}
				else if (operation[11] == ' ')
				{
					subf = (((int)operation[9] - 48) * 10) + ((int)operation[10] - 48) - 1;
					subs = (int)operation[12] - 49;
				}
			}
			else if (operation.length() == 12)
			{
				subf = (int)operation[9] - 49;
				subs = (int)operation[11] - 49;
			}															//5sayed+8ahmed+7eslam+4mohamed+6ali+2ebrahim-5ahmed=5 
			else
				break;													//5ahmed+7sayed+2mahmoud-6eslam+4ebrahim+9mohamed+8ali-3sobhy+4reda=8  
			if (subf >= n || subs >= n)									//ali+sayed-eslam+ebrahim+mahmoud+ahmed+mohamed+sobhy+reda=19-10 
				break;													//3abc-4xyz-klm=5-6def //4def-6xyz-9+3iee=abc-2	//abc-oop+5def=9+you

			int I = gsimTerm[subf];
			for (int J = gsimTerm[subs]; J < countOperators(eq[subs]) + gTransTerm[subs]; J++)
			{
				if (T[subf][I].getVar() == T[subs][J].getVar())
				{
					sub.setLTerm(T[subf][I].getCoeff() - T[subs][J].getCoeff(), T[subf][I].getVar());
					sSub = to_string(sub.getCoeff());
					if (sSub.find('-') == -1 && I != gsimTerm[subf])
						cout << "+" << sub.getCoeff() << sub.getVar();
					else
						cout << sub.getCoeff() << sub.getVar();
				}
				if (eq[subf].find(T[subs][J].getVar()) == -1)
				{
					if (TCS[subs][J].find('-') != -1)
					{
						T[subs][J].setCoeff(-T[subs][J].getCoeff());
						cout << "+" << T[subs][J].getCoeff() << T[subs][J].getVar();
						T[subs][J].setCoeff(-T[subs][J].getCoeff());
					}
					else
						cout << "-" << T[subs][J].getCoeff() << T[subs][J].getVar();
					I--;
				}
				if (eq[subs].find(T[subf][I].getVar()) == -1)
				{
					if (TCS[subf][I].find('-') == -1)
						cout << "+" << T[subf][I].getCoeff() << T[subf][I].getVar();
					else
						cout << T[subf][I].getCoeff() << T[subf][I].getVar();
					I++;
				}
				I++;
			}
			cout << "=" << gsum[subf] - gsum[subs] << endl;
		}
		else if (operation.substr(0, 8) == "subtract")
		{
			if (operation.length() == 14)
			{
				subf = (((int)operation[9] - 48) * 10) + ((int)operation[10] - 48) - 1;
				subs = (((int)operation[12] - 48) * 10) + ((int)operation[13] - 48) - 1;
			}
			else if (operation.length() == 13)
			{
				if (operation[10] == ' ')
				{
					subf = (int)operation[9] - 49;
					subs = (((int)operation[11] - 48) * 10) + ((int)operation[12] - 48) - 1;
				}
				else if (operation[11] == ' ')
				{
					subf = (((int)operation[9] - 48) * 10) + ((int)operation[10] - 48) - 1;
					subs = (int)operation[12] - 49;
				}
			}
			else if (operation.length() == 12)
			{
				subf = (int)operation[9] - 49;
				subs = (int)operation[11] - 49;
			}															//5sayed+8ahmed+7eslam+4mohamed+6ali+2ebrahim-5ahmed=5 
			else
				break;													//5ahmed+7sayed+2mahmoud-6eslam+4ebrahim+9mohamed+8ali-3sobhy+4reda=8  
			if (subf >= n || subs >= n)									//ali+sayed-eslam+ebrahim+mahmoud+ahmed+mohamed+sobhy+reda=19-10 
				break;													//3abc-4xyz-klm=5-6def //4def-6xyz-9+3iee=abc-2	//abc-oop+5def=9+you
																		
			int I = gsimTerm[subf];
			for (int J = gsimTerm[subs]; J < countOperators(eq[subs]) + gTransTerm[subs]; J++)
			{
				if (T[subf][I].getVar() == T[subs][J].getVar())
				{
					sub.setLTerm(T[subf][I].getCoeff() - T[subs][J].getCoeff(), T[subf][I].getVar());
					sSub = to_string(sub.getCoeff());
					if (sSub.find('-') == -1 && I != gsimTerm[subf])
						cout << "+" << sub.getCoeff() << sub.getVar();
					else
						cout << sub.getCoeff() << sub.getVar();
				}
				if (eq[subf].find(T[subs][J].getVar()) == -1)
				{
					if (TCS[subs][J].find('-') != -1)
					{
						T[subs][J].setCoeff(-T[subs][J].getCoeff());
						cout << "+" << T[subs][J].getCoeff() << T[subs][J].getVar();
						T[subs][J].setCoeff(-T[subs][J].getCoeff());
					}
					else
						cout << "-" << T[subs][J].getCoeff() << T[subs][J].getVar();
					I--;
				}
				if (eq[subs].find(T[subf][I].getVar()) == -1)
				{
					if (TCS[subf][I].find('-') == -1)
						cout << "+" << T[subf][I].getCoeff() << T[subf][I].getVar();
					else
						cout << T[subf][I].getCoeff() << T[subf][I].getVar();
					I++;
				}
				I++;
			}
			cout << "=" << gsum[subf] - gsum[subs] << endl;
		}
		else if (operation.substr(0, 10) == "substitute")
		{
			variable = operation.substr(11, operation.find(' ', 11) - 11);
			if (operation.length() == variable.length() + 17)
			{
				subtf = (((int)operation[variable.length() + 12] - 48) * 10) + ((int)operation[variable.length() + 13] - 48) - 1;
				subts = (((int)operation[variable.length() + 15] - 48) * 10) + ((int)operation[variable.length() + 16] - 48) - 1;
			}
			else if (operation.length() == variable.length() + 16)
			{
				if (operation[variable.length() + 13] == ' ')
				{
					subtf = (int)operation[variable.length() + 12] - 49;
					subts = (((int)operation[variable.length() + 14] - 48) * 10) + ((int)operation[variable.length() + 15] - 48) - 1;
				}
				else if (operation[variable.length() + 14] == ' ')
				{
					subtf = (((int)operation[variable.length() + 12] - 48) * 10) + ((int)operation[variable.length() + 13] - 48) - 1;
					subts = (int)operation[variable.length() + 15] - 49;
				}
			}
			else if (operation.length() == variable.length() + 15)
			{
				subtf = (int)operation[variable.length() + 12] - 49;
				subts = (int)operation[variable.length() + 14] - 49;
			}
			else
				break;
			if (subtf >= n || subts >= n || eq[subtf].find(variable) == -1 || eq[subts].find(variable) == -1)
				break;
			for (int I = gsimTerm[subtf]; I < countOperators(eq[subtf]) + gTransTerm[subtf]; I++)
			{
				if (T[subtf][I].getVar() == variable)
				{
					fc = T[subtf][I].getCoeff();
					fcs = to_string(fc);
					break;
				}
			}
			for (int I = gsimTerm[subtf]; I < countOperators(eq[subtf]) + gTransTerm[subtf]; I++)
			{
				if (fcs.find('-') == -1)
				{
					ST[0][I].setLTerm((T[subtf][I].getCoeff() / fc), T[subtf][I].getVar());
					CS[0][I] = to_string(ST[0][I].getCoeff());
					gsum[subtf] / fc;
				}
				else
				{
					ST[0][I].setLTerm((T[subtf][I].getCoeff() / -fc), T[subtf][I].getVar());
					CS[0][I] = to_string(ST[0][I].getCoeff());
					gsum[subtf] / -fc;
				}
			}
			for (int J = gsimTerm[subts]; J < countOperators(eq[subts]) + gTransTerm[subts]; J++)
			{
				if (T[subts][J].getVar() == variable)
				{
					sc = T[subts][J].getCoeff();
					scs = to_string(sc);
					break;
				}
			}
			for (int J = gsimTerm[subts]; J < countOperators(eq[subts]) + gTransTerm[subts]; J++)
			{
				if (scs.find('-') == -1)
				{
					ST[1][J].setLTerm((T[subts][J].getCoeff() / -sc), T[subts][J].getVar());
					CS[1][J] = to_string(ST[1][J].getCoeff());
					gsum[subts] / -sc;
				}
				else
				{
					ST[1][J].setLTerm((T[subts][J].getCoeff() / sc), T[subts][J].getVar());
					CS[1][J] = to_string(ST[1][J].getCoeff());
					gsum[subts] / sc;
				}
			}
			int I = gsimTerm[subtf];
			for (int J = gsimTerm[subts]; J < countOperators(eq[subts]) + gTransTerm[subts]; J++)
			{
				if (ST[0][I].getVar() == variable && ST[1][J].getVar() == variable)
				{
					I++;
					J++;
					tem = I;
					myFlag = 1;
				}
				if (ST[0][I].getVar() == ST[1][J].getVar() && ST[0][I].getVar() != variable && ST[1][J].getVar() != variable)
				{
					add.setLTerm(ST[0][I].getCoeff() + ST[1][J].getCoeff(), ST[0][I].getVar());
					sAdd = to_string(add.getCoeff());
					if (sAdd.find('-') == -1 && I != gsimTerm[subtf] && I != tem || myFlag == 0)
						cout << "+" << add.getCoeff() << add.getVar();
					else
						cout << add.getCoeff() << add.getVar();
				}
				if (eq[subtf].find(ST[1][J].getVar()) == -1)
				{
					if (CS[1][J].find('-') == -1)
						cout << "+" << ST[1][J].getCoeff() << ST[1][J].getVar();
					else
						cout << ST[1][J].getCoeff() << ST[1][J].getVar();
					I++;
				}
				if (eq[subts].find(ST[0][I].getVar()) == -1)
				{
					if (CS[0][I].find('-') == -1)
						cout << "+" << ST[0][I].getCoeff() << ST[0][I].getVar();
					else
						cout << ST[0][I].getCoeff() << ST[0][I].getVar();
					I--;
				}
				I++;
			}
			cout << "=" << gsum[subtf] + gsum[subts] << endl;
		}
		else if (operation == "D")
		{
			for (int i = 0; i < n; i++)
			{
				for (int M = 0; M < count; M++)
					cout << D[M][i].getCoeff() << "\t";
				cout << endl;
			}
		}
		else if (operation.length() > 1 && operation[0] == 'D' && operation != "D_value")
		{
			cram = operation.substr(2);
			for (int i = 0; i < n; i++)
			{
				for (int M = 0; M < count; M++)
				{
					if (D[M][i].getVar() == cram)
						cout << gsum[i] << "\t";
					else
						cout << D[M][i].getCoeff() << "\t";
				}
				cout << endl;
			}
		}
		else if (operation == "D_value")
		{
			for (int z = 0; z < n; z++)
				det = det * C[z][z];
			if (swap % 2 == 0)
				cout << det << endl;
			else
			{
				det = -det;
				cout << det << endl;
			}
		}
		else if (operation == "solve")
		{
			S[n - 1] = dsum[n - 1] / C[n - 1][n - 1];
			for (int i = n - 2; i > -1; i--)
			{
				for (int M = i + 1; M < count; M++)
				{
					so[M] = C[i][M] * S[M];
					sol[i] = sol[i] + so[M];
					S[i] = (dsum[i] - sol[i]) / C[i][i];
				}
			}
			for (int i = 0; i < n; i++)
				cout << vars[i] << "=" << S[i] << endl;
		}
		else
			break;
		getline(cin >> ws, operation);
	}
	return 0;
}
int countOperators(string s)
{
	int end = s.rfind('='), count = 1;
	for (int i = 0; i <end; i++)
		if (s[i] == '+' || s[i] == '-' || s[i] == '=')
			count++;
	return count;
}
int rCountOperators(string s)
{
	int end = s.rfind('='), count = 1;
	for (int i = end; i < s.length(); i++)
		if (s[i] == '+' || s[i] == '-' || s[i] == '=')
			count++;
	return count;
}
