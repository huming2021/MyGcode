
#include <iostream>
#include <stdio.h>
#include <vector>
#include <math.h>
#include <cstring>

#define pi 3.1415926

void test1()
{
    double X = 0.0, Y = 0.0, Z = 0.0, E = 0.0;

	FILE* fp = NULL;
	fopen_s(&fp, "E:\\6266\\test.gcode", "w");
	if (fp == NULL) { return; }

    fprintf(fp, "START_PRINT EXTRUDER_TEMP=220 BED_TEMP=45\n");

	//fprintf(fp, "SET_VELOCITY_LIMIT VELOCITY=100\n");
	//fprintf(fp, "SET_VELOCITY_LIMIT ACCEL=500\n");
	//fprintf(fp, "SET_VELOCITY_LIMIT SQUARE_CORNER_VELOCITY=5\n");

	fprintf(fp, "M82\n");
	fprintf(fp, "G90\n");
	fprintf(fp, "G92 E%7.5f\n", E);

	E -= 0.5;
	fprintf(fp, "G1 F2400 E%7.5f\n", E);
	E += 0.15;
	fprintf(fp, "G1 F2400 E%7.5f\n", E);
	E -= 0.15;
	fprintf(fp, "G1 F2400 E%7.5f\n", E);
	Z += 0.3;
	fprintf(fp, "G1 F600 Z%3.1f\n", Z);

	double Radius = 20.0;                  
	X = 110.0 - Radius;
	Y = 110.0;
	fprintf(fp, "G1 F14400 X%7.5f Y%7.5f\n", X, Y);

	Z -= 0.1;
	fprintf(fp, "G1 F600 Z%3.1f\n", Z);

	double rote = 0.0314;

	double X0 = X;
	double Y0 = Y;
	for (int j = 0; j < 50; j++)
	{
		E += 0.5;
		fprintf(fp, "G1 F2400 E%7.5f\n", E);

		for (int i = 1; i <= 120; i++)
		{
			double C = -180.0 + 3.0 * i;
			X = Radius * cos(C / 180.0 * pi) + 110.0;
			Y = Radius * sin(C / 180.0 * pi) + 110.0;
			double L = sqrt((X - X0)*(X - X0) + (Y - Y0)*(Y - Y0));
			E += (rote * L);
			fprintf(fp, "G1 F1200 X%7.5f Y%7.5f E%7.5f\n", X, Y, E);
			X0 = X;
			Y0 = Y;
		}

		E -= 0.5;
		fprintf(fp, "G1 F2400 E%7.5f\n", E);



		Z += 0.2;
		fprintf(fp, "G1 F600 Z%3.1f\n", Z);
	}

	fprintf(fp, "M106 S0\n");
	fprintf(fp, "M106 P2 S0\n");
	fprintf(fp, "END_PRINT\n");
    fclose(fp);
    return;
}

void test2()
{
	double X = 0.0, Y = 0.0, Z = 0.0, E = 0.0;

	FILE* fp = NULL;
	fopen_s(&fp, "E:\\6266\\test.gcode", "w");
	if (fp == NULL) { return; }

	fprintf(fp, "START_PRINT EXTRUDER_TEMP=220 BED_TEMP=45\n");

	fprintf(fp, "SET_VELOCITY_LIMIT VELOCITY=100\n");
	fprintf(fp, "SET_VELOCITY_LIMIT ACCEL=500\n");
	fprintf(fp, "SET_VELOCITY_LIMIT SQUARE_CORNER_VELOCITY=5\n");

	fprintf(fp, "M82\n");
	fprintf(fp, "G90\n");
	fprintf(fp, "G92 E%7.5f\n", E);

	E -= 0.5;
	fprintf(fp, "G1 F2400 E%7.5f\n", E);
	E += 0.15;
	fprintf(fp, "G1 F2400 E%7.5f\n", E);
	E -= 0.15;
	fprintf(fp, "G1 F2400 E%7.5f\n", E);
	Z += 0.3;
	fprintf(fp, "G1 F600 Z%3.1f\n", Z);

	double Radius = 20.0;                  
	X = 110.0 - Radius;
	Y = 110.0;
	fprintf(fp, "G1 F14400 X%7.5f Y%7.5f\n", X, Y);

	Z -= 0.1;
	fprintf(fp, "G1 F600 Z%3.1f\n", Z);

	double rote = 0.0314;     
	//double delta = 0.45;

	double X0 = X;
	double Y0 = Y;
	for (int j = 0; j < 100; j++)
	{
		//double delta = 0.45 - 0.001256 * j;

		//if (j <= 100) { delta = 0.45; }
		//else { delta = 0.2; }

		double delta = 0.3771;

		E += 0.5;
		fprintf(fp, "G1 F2400 E%7.5f\n", E);

		for (int i = 1; i <= 120; i++)
		{
			double C = -180.0 + 3.0 * i;
			X = Radius * cos(C / 180.0 * pi) + 110.0;
			Y = Radius * sin(C / 180.0 * pi) + 110.0;
			double L = sqrt((X - X0) * (X - X0) + (Y - Y0) * (Y - Y0));
			E += (rote * L);
			fprintf(fp, "G1 F6000 X%7.5f Y%7.5f E%7.5f\n", X, Y, E);
			X0 = X;
			Y0 = Y;
		}

		E -= 0.5;
		fprintf(fp, "G1 F2400 E%7.5f\n", E);

		X -= delta;
		fprintf(fp, "G1 F14400 X%7.5f\n", X);
		X0 = X;
		Y0 = Y;

		E += 0.5;
		fprintf(fp, "G1 F2400 E%7.5f\n", E);
		for (int i = 1; i <= 120; i++)
		{
			double C = -180.0 + 3.0 * i;
			X = (Radius + delta) * cos(C / 180.0 * pi) + 110.0;
			Y = (Radius + delta) * sin(C / 180.0 * pi) + 110.0;
			double L = sqrt((X - X0) * (X - X0) + (Y - Y0) * (Y - Y0));
			E += (rote * L);
			fprintf(fp, "G1 F6000 X%7.5f Y%7.5f E%7.5f\n", X, Y, E);
			X0 = X;
			Y0 = Y;
		}

		E -= 0.5;
		fprintf(fp, "G1 F2400 E%7.5f\n", E);

		Z += 0.2;
		fprintf(fp, "G1 F600 Z%3.1f\n", Z);

		X += delta;
		fprintf(fp, "G1 F14400 X%7.5f\n", X);
		X0 = X;
		Y0 = Y;
	}

	fprintf(fp, "M106 S0\n");
	fprintf(fp, "M106 P2 S0\n");
	fprintf(fp, "END_PRINT\n");
	fclose(fp);
	return;
}

struct MyPoint3d
{
	double X, Y, Z;
	MyPoint3d(double a, double b, double c)
	{
		this->X = a;
		this->Y = b;
		this->Z = c;
	}
	MyPoint3d()
	{
		memset(this, 0, sizeof(MyPoint3d));
	}
};
double dis(MyPoint3d a, MyPoint3d b)
{
	double dx = b.X - a.X;
	double dy = b.Y - a.Y;
	double dz = b.Z - a.Z;
	return sqrt(dx * dx + dy * dy + dz * dz);
}
enum myfeature
{
	travel = 0,
	extrusion = 1,
	Zup = 2,
};
struct MySegment
{
	MyPoint3d P0, P1;
	myfeature F;
	double len;
	MySegment(MyPoint3d a, MyPoint3d b, myfeature c)
	{
		this->P0 = a;
		this->P1 = b;
		this->F  = c;
		this->len = dis(a, b);
	}
};

void test3()
{
	std::vector<MyPoint3d> ToolPath;

	FILE* fp = NULL;
	fopen_s(&fp, "E:\\6266\\test.gcode", "w");
	if (fp == NULL) { return; }

	double Radius = 20.0;
	double delta = 0.3771;
	double rote = 0.0314;

	double Z = 0.0;

	for (int j = 0; j < 100; j++)
	{
		Z += 0.2;
		for (int i = 0; i <= 120; i++)
		{
			double C = -180.0 + 3.0 * i;
			double X = Radius * cos(C / 180.0 * pi);
			double Y = Radius * sin(C / 180.0 * pi);
			MyPoint3d a(X, Y, Z);
			ToolPath.push_back(a);
		}
		Radius += delta;
		for (int i = 0; i <= 120; i++)
		{
			double C = -180.0 + 3.0 * i;
			double X = Radius * cos(C / 180.0 * pi);
			double Y = Radius * sin(C / 180.0 * pi);
			MyPoint3d a(X, Y, Z);
			ToolPath.push_back(a);
		}
		Radius -= delta;
	}

	std::vector<MySegment> Path;
	for (size_t i = 1; i < ToolPath.size(); i++)
	{
		MyPoint3d a = ToolPath[i - 1];
		MyPoint3d b = ToolPath[i];
		double len = dis(a, b);
		// unsigned char f = (len < 0.5) ? 0 : 1;   //travel = 0, extrude = 1;
		myfeature f = (len < 0.5) ? Zup:extrusion;
		MySegment s(a, b, f);
		Path.push_back(s);
	}
	std::vector<MyPoint3d>().swap(ToolPath);

	fprintf(fp, "START_PRINT EXTRUDER_TEMP=220 BED_TEMP=45\n");

	double E = 0.0;

	fprintf(fp, "M82\n");
	fprintf(fp, "G90\n");
	fprintf(fp, "G92 E%7.5f\n", E);

	E -= 0.5;
	fprintf(fp, "G1 F2400 E%7.5f\n", E);
	E += 0.15;
	fprintf(fp, "G1 F2400 E%7.5f\n", E);
	E -= 0.15;
	fprintf(fp, "G1 F2400 E%7.5f\n", E);

	MyPoint3d P0 = ToolPath[0];     //error
	fprintf(fp, "G1 F600 Z%3.1f\n", P0.Z + 0.1);
	fprintf(fp, "G0 X%7.5f Y%7.5f\n", P0.X, P0.Y);   
	fprintf(fp, "G1 F600 Z%3.1f\n", P0.Z);

	E += 0.5;
	fprintf(fp, "G1 F2400 E%7.5f\n", E);

	for (size_t i = 0; i < Path.size(); i++)
	{
		MySegment s = Path[i];
		MyPoint3d P1 = s.P1;
		if (s.F == travel)    //travel
		{
			E -= 0.5;
			fprintf(fp, "G1 F2400 E%7.5f\n", E);
			fprintf(fp, "G0 X%7.5f Y%7.5f Z%7.5f\n", P1.X, P1.Y, P1.Z);
			E += 0.5;
			fprintf(fp, "G1 F2400 E%7.5f\n", E);
		}
		else
		{
			E += (s.len * rote);
			fprintf(fp, "G1 F6000 X%7.5f Y%7.5f E%7.5f\n", P1.X, P1.Y, E);
		}
	}

	fprintf(fp, "M106 S0\n");
	fprintf(fp, "M106 P2 S0\n");
	fprintf(fp, "END_PRINT\n");
	fclose(fp);

	return;
}
void test4()
{
	std::vector<MyPoint3d> ToolPath;

	FILE* fp = NULL;
	fopen_s(&fp, ".\\test.gcode", "w");
	if (fp == NULL) { return; }

	double Radius = 20.0;
	double rote = 0.0349;     //layer_height=0.2, line_width=0.42, flow_rote=100%
	double layer_height = 0.2;

	for(size_t i = 0; i < 50; i++)
	{
		double Z = layer_height*(i + 1);
		for(size_t j = 0; j <= 120; j++)
		{
			double C = -180.0 + 3.0*j;
			double X = Radius*cos(C/180.0*pi);
			double Y = Radius*sin(C/180.0*pi);
			MyPoint3d a(X, Y, Z);
			ToolPath.push_back(a);
		}
	}

	// for(size_t i = 0; i < ToolPath.size(); i++)
	// {
	// 	MyPoint3d a = ToolPath[i];
	// 	fprintf(fp, "X%lf Y%lf Z%lf\n", a.X, a.Y, a.Z);
	// }

	std::vector<MySegment> Path;
	for(size_t i = 1; i < ToolPath.size(); i++)
	{
		MyPoint3d a = ToolPath[i - 1];
		MyPoint3d b = ToolPath[i];
		myfeature f = (fabs(a.Z - b.Z) > 0.1)?Zup:extrusion;
		MySegment c(a, b, f);
		Path.push_back(c);
	}
	std::vector<MyPoint3d>().swap(ToolPath);

	fprintf(fp, "START_PRINT EXTRUDER_TEMP=220 BED_TEMP=45\n");

	double E = 0.0;

	fprintf(fp, "M82\n");
	fprintf(fp, "G90\n");
	fprintf(fp, "G92 E%7.5f\n", E);

	E -= 0.5;
	fprintf(fp, "G1 F2400 E%7.5f\n", E);
	E += 0.15;
	fprintf(fp, "G1 F2400 E%7.5f\n", E);
	E -= 0.15;
	fprintf(fp, "G1 F2400 E%7.5f\n", E);

	MyPoint3d P0 = Path[0].P0;     
	fprintf(fp, "G1 F600 Z%3.1f\n", P0.Z + 0.1);
	fprintf(fp, "G0 X%7.5f Y%7.5f\n", P0.X, P0.Y);   
	fprintf(fp, "G1 F600 Z%3.1f\n", P0.Z);

	double F_extrusion = 100.0*60.0;   
	double F_travel = 500.0*60.0;
	double F_Zup = 600.0;

	E += 0.5;
	fprintf(fp, "G1 F2400 E%7.5f\n", E);

	for(size_t i = 0; i < Path.size(); i++)
	{
		MySegment s = Path[i];
		MyPoint3d p = s.P1;

		if(s.F == extrusion)
		{
			E += (s.len * rote);
			fprintf(fp, "G1 F%d X%7.5f Y%7.5f E%7.5f\n", (int)F_extrusion, p.X, p.Y, E);
		}
		else if(s.F == Zup)
		{
			// fprintf(fp, "G1 F%7.5f X%7.5f Y%7.5f Z%7.5f\n", F_Zup, p.X, p.Y, p.Z);
			fprintf(fp, "G1 F%d Z%7.5f\n", (int)F_Zup, p.Z);
		}
		else
		{

		}

		if(i != Path.size() - 1)
		{
			if(Path[i + 1].F == Zup && s.F == extrusion)
			{
				E -= 0.5;
				fprintf(fp, "G1 F2400 E%7.5f\n", E);
			}
			if(Path[i + 1].F == extrusion && s.F == Zup)
			{
				E += 0.5;
				fprintf(fp, "G1 F2400 E%7.5f\n", E);
			}
		}
	}

	E -= 0.5;
	fprintf(fp, "G1 F2400 E%7.5f\n", E);

	fprintf(fp, "M106 S0\n");
	fprintf(fp, "M106 P2 S0\n");
	fprintf(fp, "END_PRINT\n");
	fclose(fp);
	return;
}
int main()
{
    //test1();
	//test2();
	//test3();
	test4();
}