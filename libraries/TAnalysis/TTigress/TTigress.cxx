
#include <iostream>
#include "TTigress.h"

#include <TRandom.h>
#include <TMath.h>

ClassImp(TTigress)

double TTigress::beta = 0.0;

bool TTigress::fSetSegmentHits = true;
bool TTigress::fSetBGOHits = true;

bool TTigress::fSetCoreWave = false;
bool TTigress::fSetSegmentWave = false;
bool TTigress::fSetBGOWave = false;


TTigress::TTigress()	{
	Clear();
}

TTigress::~TTigress()	{	}

void TTigress::Clear(Option_t *opt)	{

	TCrystalData::Clear();
	TBGOData::Clear();

	tigress_hits.clear();
	addback_hits.clear();

}


void	TTigress::BuildHits()	{
	//Clear();

	TCrystalHit *temp_crystal = new TCrystalHit();

	//TRandom rand;
	//rand.SetSeed();
	//First build the core hits.
	for(int i=0;i<GetCoreMultiplicity();i++)	{
		TTigressHit corehit;
		temp_crystal->Clear();

                temp_crystal->SetCharge(GetCoreCharge(i));
                temp_crystal->SetEnergy(GetCoreEnergy(i));
                temp_crystal->SetTime(GetCoreTime(i));
                temp_crystal->SetCfd(GetCoreCFD(i));

		if(fSetCoreWave)	{
                	temp_crystal->SetWave(GetCoreWave(i));
		}
		
		corehit.SetCore(*temp_crystal);	
		corehit.SetDetectorNumber(GetCloverNumber(i));
        corehit.SetCrystalNumber(GetCoreNumber(i));

		tigress_hits.push_back(corehit);
	}

	//sort ??
	
	for(int i=0;i<tigress_hits.size();i++)	{
	   for(int j=0;j<GetSegmentMultiplicity();j++)	{
	      if((tigress_hits[i].GetDetectorNumber() == GetSegCloverNumber(j))  && (tigress_hits[i].GetCrystalNumber() == GetSegCoreNumber(j))) {
	         tigress_hits[i].CheckFirstHit(GetSegmentCharge(j),GetSegmentNumber(j));
                 if(fSetSegmentHits)   {		
                    temp_crystal->Clear();

                    temp_crystal->SetSegmentNumber(GetSegmentNumber(j));

                    temp_crystal->SetCharge(GetSegmentCharge(j));
                    temp_crystal->SetEnergy(GetSegmentEnergy(j));
                    temp_crystal->SetTime(GetSegmentTime(j));
                    temp_crystal->SetCfd(GetSegmentCFD(j));

                    if(fSetSegmentWave) {
                       temp_crystal->SetWave(GetSegmentWave(j));
                    }
                    tigress_hits[i].SetSegment(*temp_crystal);
                 }
	      }	
	   }
           if(fSetBGOHits)  {
              for(int j=0;j<GetBGOMultiplicity();j++)  {
	         if((tigress_hits[i].GetDetectorNumber() == GetBGOCloverNumber(j))  && (tigress_hits[i].GetCrystalNumber() == GetBGOCoreNumber(j))) {
		    temp_crystal->Clear();

                    temp_crystal->SetSegmentNumber(GetBGOPmNbr(j));

                    temp_crystal->SetCharge(GetBGOCharge(j));
                    temp_crystal->SetEnergy(GetBGOEnergy(j));
                    temp_crystal->SetTime(GetBGOTime(j));
                    temp_crystal->SetCfd(GetBGOCFD(j));

                    if(fSetBGOWave) {
                       temp_crystal->SetWave(GetBGOWave(j));
                    }			
		    tigress_hits[i].SetBGO(*temp_crystal);	
                 }
              }
           }
	}



	delete temp_crystal;

}

double TTigress::GetDopplerEnergy(TTigressHit *hit)	{

}



TVector3 TTigress::GetPosition(TTigressHit *hit)  {
	return TTigress::GetPosition(hit->GetDetectorNumber(),hit->GetCrystalNumber(),hit->GetInitialHit());	
}

TVector3 TTigress::GetPosition(int DetNbr,int CryNbr,int SegNbr)	{

	TVector3 det_pos;
	double xx = 0;
	double yy = 0;
	double zz = 0;
	
	//printf("xx = %f\nyy = %f\n zz = %f\n",GeBlue_Position[DetNbr][SegNbr][0],GeBlue_Position[DetNbr][SegNbr][1],GeBlue_Position[DetNbr][SegNbr][2]);
		

	switch(CryNbr)	{
		case -1:
			break;
		case 0:
			xx = GeBlue_Position[DetNbr][SegNbr][0];
			yy = GeBlue_Position[DetNbr][SegNbr][1];
			zz = GeBlue_Position[DetNbr][SegNbr][2];
			break;
		case 1:
			xx = GeGreen_Position[DetNbr][SegNbr][0]; 
			yy = GeGreen_Position[DetNbr][SegNbr][1]; 
			zz = GeGreen_Position[DetNbr][SegNbr][2]; 
			break;
		case 2:
			xx = GeRed_Position[DetNbr][SegNbr][0]; 
			yy = GeRed_Position[DetNbr][SegNbr][1]; 
			zz = GeRed_Position[DetNbr][SegNbr][2];  
			break;
		case 3:
			xx = GeWhite_Position[DetNbr][SegNbr][0]; 
			yy = GeWhite_Position[DetNbr][SegNbr][1]; 
			zz = GeWhite_Position[DetNbr][SegNbr][2]; 
			break;
	};
	//printf("xx = %f\nyy = %f\n zz = %f\n",xx,yy,zz);
	det_pos.SetXYZ(xx,yy,zz);

	return det_pos;


	/// this function is 

/*
	double x_offset = 0;
	double y_offset = 0;
	double z_offset = 0;

	switch(SegNbr)	{
		case -1:
			break;
		case 0:
		case 9:
			x_offset = 27.2;	
			y_offset = 27.2;
			z_offset = 45.0;
			break;
		case 1:
			x_offset = 20.9+10.45;
			y_offset = 20.9+10.45;
			z_offset = 18.1;
			break;
		case 2:
			x_offset = 10.45;
			y_offset = 20.9+10.45;
			z_offset = 18.1;
			break;
		case 3:
			x_offset = 10.45;
			y_offset = 10.45;
			z_offset = 18.1;	
			break;
		case 4:
			x_offset =  20.9 + 10.45;	
			y_offset = 10.45;
			z_offset = 18.1;
			break;
		case 5:
			x_offset = 27.2 + 13.6;
			y_offset = 27.2 + 13.6;
			z_offset = 63.1;
			break;
		case 6:
			x_offset = 13.6;
			y_offset = 27.2 + 13.6;
			z_offset = 63.1;	
			break;
		case 7:
			x_offset = 13.6;
			y_offset = 13.6;
			z_offset = 63.1;
			break;
		case 8:
			x_offset = 27.2 + 13.6;
			y_offset = 13.6;
			z_offset = 63.1;
			break;
		default:
			break;
	};


	if(CryNbr<0 || CryNbr >3) 
		return det_pos;

	TRotation Cry_Rot;	
	Cry_Rot.RotateZ(90*CryNbr*TMath::DegToRad());

	TRotation rot;
	TRotation rot_theta;
	TRotation rot_phi;
	bool need_to_be_mirrored = false;
	double theta;
	double phi;
	switch(DetNbr)	{
		case 1:
			phi = 22.5;
			theta = 45.0;
			break;
	 	case 2:
			phi = 112.5;
			theta = 45.0;
			need_to_be_mirrored = true;
			break;
		case 3:
			phi = 202.5;
			theta = 45.0;
			need_to_be_mirrored = true;
			break;

		case 4:
			phi = 292.5;
			theta = 45.0;
			break;
		case 5:
			phi 	= 22.5;
			theta = 90.0;
			break;
		case 6:
			phi = 67.5;
			theta = 90.0;
			break;
		case 7:
			phi = 112.5;
			theta = 90.0;
			need_to_be_mirrored = true;
			break;
		case 8:
			phi = 157.5;
			theta = 90.0;
			need_to_be_mirrored = true;
			break;
		case 9:
			phi = 202.5;		
			theta = 90.0;
			need_to_be_mirrored = true;
			break;
		case 10:
			phi = 247.5;		
			theta = 90.0;
			need_to_be_mirrored = true;
			break;
		case 11:
			phi = 292.5;		
			theta = 90.0;
			break;
		case 12:
			phi = 337.5;		
			theta = 90.0;
			break;
			break;
		case 13:
			phi = 22.5;
			theta = 145.0;
			break;
		case 14:
			phi = 112.5;
			theta = 145.0;
			need_to_be_mirrored = true;
			break;
		case 15:
			phi = 202.5;
			theta = 145.0;
			need_to_be_mirrored = true;
			break;
		case 16:
			phi = 292.5;
			theta = 145.0;
			break;
	};

	if(need_to_be_mirrored)	{
		Cry_Rot.RotateZ(180*TMath::DegToRad());
	}

	det_pos.SetXYZ(x_offset,y_offset,R+z_offset);
//	rot_theta.RotateY(theta*TMath::DegToRad());
	rot_theta.RotateX(theta*TMath::DegToRad());
//	rot_phi.RotateZ((phi)*TMath::DegToRad());
	rot_phi.RotateZ((phi)*TMath::DegToRad());
	rot =   Cry_Rot * rot_phi * rot_theta; //

	//det_pos.Transform(rot_theta);
	//det_pos.Transform(rot);
*/

/*
	std::cout << det_pos.X() <<"\t" << det_pos.Y() << "\t" << det_pos.Z() << std::endl;
	det_pos.SetXYZ(x_offset,y_offset,R+z_offset);
	rot_theta.RotateY(theta*TMath::DegToRad());
	rot_phi.RotateZ(-phi*TMath::DegToRad());
	rot =    rot_phi * rot_theta; //Cry_Rot *
	*/
//	det_pos.Transform(rot_phi);
//	det_pos.Transform(rot_theta);

	/*
*/
	//det_pos.SetZ(-det_pos.Z());
//	std::cout << det_pos.X() <<"\t" << det_pos.Y() << "\t" << det_pos.Z() << std::endl;

//	return det_pos;

}



void TTigress::BuildAddBack()	{ 
	if(tigress_hits.size() ==0	)
		return;
/*
	addback_hits.clear();
	addback_hits.push_back(tigress_hits[0]);
	std::set<int> seen;
	for(int i =1;i<GetMultiplicity();i++)	{
		bool matched = false;
		for(int j =0;j<GetAddBackMultiplicity();j++)	{
			//if(j>GetMultiplicity())
			//	break;
		
			TVector3 p1 = tigress_hits[i].position;
			TVector3 p2	=	addback_hits[j].position;		
			TVector3 res = p2-p1;
			matched = false;
			cout << "Calculated Mag: "<< res.Mag() << endl;
			if((res.Mag() < 30) &&  !(seen.insert(i).second))	{
				//do add the add back....
				p1 * tigress_hits[i].energy;
				p2 * addback_hits[j].energy;
			
				addback_hits[j].position = (p1+p2) * (1.0/(tigress_hits[i].energy + addback_hits[j].energy));
				//if(tigress_hits[i].energy > addback_hits[j].energy) 
				//	addback_hits[j].position = tigress_hits[i].position;
			

				addback_hits[j].energy += tigress_hits[i].energy;	
				
				matched = true;
			}
			if(!matched){
				addback_hits.push_back(tigress_hits[i]);
				//j++;
		    break; // end loop over j.
			}
		}
	}


 cout << "======================================================" << endl;
	
	for(short j=0;j<tigress_hits.size();j++){
		cout << j << "\t" << tigress_hits[j].energy << "\t" << tigress_hits[j].position.X() << "\t" << tigress_hits[j].position.Y() << "\t" << tigress_hits[j].position.Z() << endl;
	}

	for(short j=0;j<addback_hits.size();j++){
		cout << j << "\t" << addback_hits[j].energy << "\t" << addback_hits[j].position.X() << "\t" << addback_hits[j].position.Y() << "\t" << addback_hits[j].position.Z() << endl;
	}
 cout << "======================================================" << endl;
*/
	
}







double TTigress::GeBlue_Position[17][9][3] = { 
{ { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } },
{ { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } },
{ { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } },
{ { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } },
{ { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } },
{ { 139.75, 87.25, 27.13 }, { 107.47, 84.35, 36.80 }, { 107.64, 84.01, 12.83 }, { 116.86, 63.25, 13.71 }, { 116.66, 62.21, 36.42 }, { 146.69, 104.60, 40.50 }, { 146.58, 104.81, 14.96 }, { 156.50, 80.77, 14.73 }, { 156.44, 80.99, 40.74 } },
{ { 37.12, 160.51, 27.13 }, { 16.35, 135.64, 36.80 }, { 16.71, 135.51, 12.83 }, { 37.91, 127.36, 13.71 }, { 38.50, 126.48, 36.42 }, { 29.76, 177.69, 40.50 }, { 29.53, 177.76, 14.96 }, { 53.55, 167.78, 14.73 }, { 53.35, 167.89, 40.74 } },
{ {-87.25, 139.75, 27.13}, {-84.35, 107.47, 36.80}, {-84.01, 107.64, 12.83}, {-63.25, 116.86, 13.71}, {-62.21, 116.66, 36.42}, {-104.60, 146.69, 40.50}, {-104.81, 146.58, 14.96}, {-80.77, 156.50, 14.73}, {-80.99, 156.44, 40.74} },
{ {-160.51, 37.12, 27.13}, {-135.64, 16.35, 36.80}, {-135.51, 16.71, 12.83}, {-127.36, 37.91, 13.71}, {-126.48, 38.50, 36.42}, {-177.69, 29.76, 40.50}, {-177.76, 29.53, 14.96}, {-167.78, 53.55, 14.73}, {-167.89, 53.35, 40.74} },
{ {-139.75, -87.25, 27.13}, {-107.47, -84.35, 36.80}, {-107.64, -84.01, 12.83}, {-116.86, -63.25, 13.71}, {-116.66, -62.21, 36.42}, {-146.69, -104.60, 40.50}, {-146.58, -104.81, 14.96}, {-156.50, -80.77, 14.73}, {-156.44, -80.99, 40.74} },
{ {-37.12, -160.51, 27.13}, {-16.35, -135.64, 36.80}, {-16.71, -135.51, 12.83}, {-37.91, -127.36, 13.71}, {-38.50, -126.48, 36.42}, {-29.76, -177.69, 40.50}, {-29.53, -177.76, 14.96}, {-53.55, -167.78, 14.73}, {-53.35, -167.89, 40.74} },
{ {87.25, -139.75, 27.13}, {84.35, -107.47, 36.80}, {84.01, -107.64, 12.83}, {63.25, -116.86, 13.71}, {62.21, -116.66, 36.42}, {104.60, -146.69, 40.50}, {104.81, -146.58, 14.96}, {80.77, -156.50, 14.73}, {80.99, -156.44, 40.74} },
{ {160.51, -37.12, 27.13}, {135.64, -16.35, 36.80}, {135.51, -16.71, 12.83}, {127.36, -37.91, 13.71}, {126.48, -38.50, 36.42}, {177.69, -29.76, 40.50}, {177.76, -29.53, 14.96}, {167.78, -53.55, 14.73}, {167.89, -53.35, 40.74} },
{ {113.50, 76.38, -95.72}, {95.91, 79.56, -67.01}, {80.41, 72.73, -83.98}, {90.05, 52.14, -83.76}, {104.85, 57.32, -67.30}, {125.64, 95.88, -95.49}, {108.85, 89.19, -113.54}, {118.64, 65.08, -113.68}, {135.56, 72.34, -95.31} },
{ {-76.38, 113.5, -95.72}, {-79.56, 95.91, -67.01}, {-72.73, 80.41, -83.98}, {-52.14, 90.05, -83.76}, {-57.32, 104.85, -67.30}, {-95.88, 125.64, -95.49}, {-89.19, 108.85, -113.54}, {-65.08, 118.64, -113.68}, {-72.34, 135.56, -95.31} },
{ {-113.50, -76.38, -95.72}, {-95.91, -79.56, -67.01}, {-80.41, -72.73, -83.98}, {-90.05, -52.14, -83.76}, {-104.85, -57.32, -67.30}, {-125.64, -95.88, -95.49}, {-108.85, -89.19, -113.54}, {-118.64, -65.08, -113.68}, {-135.56, -72.34, -95.31} },
{ {76.38, -113.50, -95.72}, {79.56, -95.91, -67.01}, {72.73, -80.41, -83.98}, {52.14, -90.05, -83.76}, {57.32, -104.85, -67.30}, {95.88, -125.64, -95.49}, {89.19, -108.85, -113.54}, {65.08, -118.64, -113.68}, {72.34, -135.56, -95.31} }
};

//Assuming this is the 1
double TTigress::GeGreen_Position[17][9][3] = { 
{ { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } },
{ { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } },
{ { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } },
{ { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } },
{ { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } },
{ { 139.75, 87.25, -27.13 }, { 107.47, 84.35, -36.80 }, { 116.66, 62.21, -36.42 }, { 116.86, 63.25, -13.71 }, { 107.64, 84.01, -12.83 }, { 146.69, 104.60, -40.50 }, { 156.44, 80.99, -40.74 }, { 156.50, 80.77, -14.73 }, { 146.58, 104.81, -14.96 } },
{ { 37.12, 160.51, -27.13 }, { 16.35, 135.64, -36.80 }, { 38.50, 126.48, -36.42 }, { 37.91, 127.36, -13.71 }, { 16.71, 135.51, -12.83 }, { 29.76, 177.69, -40.50 }, { 53.35, 167.89, -40.74 }, { 53.55, 167.78, -14.73 }, { 29.53, 177.76, -14.96 } },
{ {-87.25, 139.75, -27.13}, {-84.35, 107.47, -36.80}, {-62.21, 116.66, -36.42}, {-63.25, 116.86, -13.71}, {-84.01, 107.64, -12.83}, {-104.60, 146.69, -40.50}, {-80.99, 156.44, -40.74}, {-80.77, 156.50, -14.73}, {-104.81, 146.58, -14.96} },
{ {-160.51, 37.12, -27.13}, {-135.64, 16.35, -36.80}, {-126.48, 38.50, -36.42}, {-127.36, 37.91, -13.71}, {-135.51, 16.71, -12.83}, {-177.69, 29.76, -40.50}, {-167.89, 53.35, -40.74}, {-167.78, 53.55, -14.73}, {-177.76, 29.53, -14.96} },
{ {-139.75, -87.25, -27.13}, {-107.47, -84.35, -36.80}, {-116.66, -62.21, -36.42}, {-116.86, -63.25, -13.71}, {-107.64, -84.01, -12.83}, {-146.69, -104.60, -40.50}, {-156.44, -80.99, -40.74}, {-156.50, -80.77, -14.73}, {-146.58, -104.81, -14.96} },
{ {-37.12, -160.51, -27.13}, {-16.35, -135.64, -36.80}, {-38.50, -126.48, -36.42}, {-37.91, -127.36, -13.71}, {-16.71, -135.51, -12.83}, {-29.76, -177.69, -40.50}, {-53.35, -167.89, -40.74}, {-53.55, -167.78, -14.73}, {-29.53, -177.76, -14.96} },
{ {87.25, -139.75, -27.13}, {84.35, -107.47, -36.80}, {62.21, -116.66, -36.42}, {63.25, -116.86, -13.71}, {84.01, -107.64, -12.83}, {104.60, -146.69, -40.50}, {80.99, -156.44, -40.74}, {80.77, -156.50, -14.73}, {104.81, -146.58, -14.96} },
{ {160.51, -37.12, -27.13}, {135.64, -16.35, -36.80}, {126.48, -38.50, -36.42}, {127.36, -37.91, -13.71}, {135.51, -16.71, -12.83}, {177.69, -29.76, -40.50}, {167.89, -53.35, -40.74}, {167.78, -53.55, -14.73}, {177.76, -29.53, -14.96} },
{ {78.05, 61.70, -134.09}, {47.83, 59.64, -119.06}, {57.26, 37.61, -118.80}, {72.14, 44.72, -103.15}, {63.65, 65.78, -102.12}, {72.73, 73.96, -152.77}, {82.33, 50.30, -152.93}, {99.39, 57.11, -134.51}, {89.31, 81.09, -134.70} },
{ {-61.7, 78.05, -134.09}, {-59.64, 47.83, -119.06}, {-37.61, 57.26, -118.80}, {-44.72, 72.14, -103.15}, {-65.78, 63.65, -102.12}, {-73.96, 72.73, -152.77}, {-50.30, 82.33, -152.93}, {-57.11, 99.39, -134.51}, {-81.09, 89.31, -134.70} },
{ {-78.05, -61.7, -134.09}, {-47.83, -59.64, -119.06}, {-57.26, -37.61, -118.80}, {-72.14, -44.72, -103.15}, {-63.65, -65.78, -102.12}, {-72.73, -73.96, -152.77}, {-82.33, -50.30, -152.93}, {-99.39, -57.11, -134.51}, {-89.31, -81.09, -134.70} },
{ {61.7, -78.05, -134.09}, {59.64, -47.83, -119.06}, {37.61, -57.26, -118.80}, {44.72, -72.14, -103.15}, {65.78, -63.65, -102.12}, {73.96, -72.73, -152.77}, {50.30, -82.33, -152.93}, {57.11, -99.39, -134.51}, {81.09, -89.31, -134.70} }
};

//Assuming this is the 2
double TTigress::GeRed_Position[17][9][3] = { 
{ { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } },
{ { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } },
{ { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } },
{ { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } },
{ { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } },
{ { 160.51, 37.12, -27.13 }, { 135.64, 16.35, -36.80 }, { 135.51, 16.71, -12.83 }, { 127.36, 37.91, -13.71 }, { 126.48, 38.50, -36.42 }, { 177.69, 29.76, -40.50 }, { 177.76, 29.53, -14.96 }, { 167.78, 53.55, -14.73 }, { 167.89, 53.35, -40.74 } },
{ { 87.25, 139.75, -27.13 }, { 84.35, 107.47, -36.80 }, { 84.01, 107.64, -12.83 }, { 63.25, 116.86, -13.71 }, { 62.21, 116.66, -36.42 }, { 104.60, 146.69, -40.50 }, { 104.81, 146.58, -14.96 }, { 80.77, 156.50, -14.73 }, { 80.99, 156.44, -40.74 } },
{ {-37.12, 160.51, -27.13}, {-16.35, 135.64, -36.80}, {-16.71, 135.51, -12.83}, {-37.91, 127.36, -13.71}, {-38.50, 126.48, -36.42}, {-29.76, 177.69, -40.50}, {-29.53, 177.76, -14.96}, {-53.55, 167.78, -14.73}, {-53.35, 167.89, -40.74} },
{ {-139.75, 87.25, -27.13}, {-107.47, 84.35, -36.80}, {-107.64, 84.01, -12.83}, {-116.86, 63.25, -13.71}, {-116.66, 62.21, -36.42}, {-146.69, 104.60, -40.50}, {-146.58, 104.81, -14.96}, {-156.50, 80.77, -14.73}, {-156.44, 80.99, -40.74} },
{ {-160.51, -37.12, -27.13}, {-135.64, -16.35, -36.80}, {-135.51, -16.71, -12.83}, {-127.36, -37.91, -13.71}, {-126.48, -38.50, -36.42}, {-177.69, -29.76, -40.50}, {-177.76, -29.53, -14.96}, {-167.78, -53.55, -14.73}, {-167.89, -53.35, -40.74} },
{ {-87.25, -139.75, -27.13}, {-84.35, -107.47, -36.80}, {-84.01, -107.64, -12.83}, {-63.25, -116.86, -13.71}, {-62.21, -116.66, -36.42}, {-104.60, -146.69, -40.50}, {-104.81, -146.58, -14.96}, {-80.77, -156.50, -14.73}, {-80.99, -156.44, -40.74} },
{ {37.12, -160.51, -27.13}, {16.35, -135.64, -36.80}, {16.71, -135.51, -12.83}, {37.91, -127.36, -13.71}, {38.50, -126.48, -36.42}, {29.76, -177.69, -40.50}, {29.53, -177.76, -14.96}, {53.55, -167.78, -14.73}, {53.35, -167.89, -40.74} },
{ {139.75, -87.25, -27.13}, {107.47, -84.35, -36.80}, {107.64, -84.01, -12.83}, {116.86, -63.25, -13.71}, {116.66, -62.21, -36.42}, {146.69, -104.60, -40.50}, {146.58, -104.81, -14.96}, {156.50, -80.77, -14.73}, {156.44, -80.99, -40.74} },
{ {98.82, 11.57, -134.09}, {75.99, -8.35, -119.06}, {91.52, -1.51, -102.12}, {82.63, 19.39, -103.15}, {67.08, 13.90, -118.80}, {103.72, -0.87, -152.77}, {120.49, 5.81, -134.70}, {110.66, 29.90, -134.51}, {93.78, 22.65, -152.93} },
{ {-11.57, 98.82, -134.09}, {8.35, 75.99, -119.06}, {1.51, 91.52, -102.12}, {-19.39, 82.63, -103.15}, {-13.90, 67.08, -118.80}, {0.87, 103.72, -152.77}, {-5.81, 120.49, -134.70}, {-29.90, 110.66, -134.51}, {-22.65, 93.78, -152.93} },
{ {-98.82, -11.57, -134.09}, {-75.99, 8.35, -119.06}, {-91.52, 1.51, -102.12}, {-82.63, -19.39, -103.15}, {-67.08, -13.90, -118.80}, {-103.72, 0.87, -152.77}, {-120.49, -5.81, -134.70}, {-110.66, -29.90, -134.51}, {-93.78, -22.65, -152.93} },
{ {11.57, -98.82, -134.09}, {-8.35, -75.99, -119.06}, {-1.51, -91.52, -102.12}, {19.39, -82.63, -103.15}, {13.90, -67.08, -118.80}, {-0.87, -103.72, -152.77}, {5.81, -120.49, -134.70}, {29.90, -110.66, -134.51}, {22.65, -93.78, -152.93} }
};

//Assuming this is the 3
double TTigress::GeWhite_Position[17][9][3] = { 
{ { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } },
{ { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } },
{ { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } },
{ { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } },
{ { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } },
{ { 160.51, 37.12, 27.13 }, { 135.64, 16.35, 36.80 }, { 126.48, 38.50, 36.42 }, { 127.36, 37.91, 13.71 }, { 135.51, 16.71, 12.83 }, { 177.69, 29.76, 40.50 }, { 167.89, 53.35, 40.74 }, { 167.78, 53.55, 14.73 }, { 177.76, 29.53, 14.96 } },
{ { 87.25, 139.75, 27.13 }, { 84.35, 107.47, 36.80 }, { 62.21, 116.66, 36.42 }, { 63.25, 116.86, 13.71 }, { 84.01, 107.64, 12.83 }, { 104.60, 146.69, 40.50 }, { 80.99, 156.44, 40.74 }, { 80.77, 156.50, 14.73 }, { 104.81, 146.58, 14.96 } },
{ {-37.12, 160.51, 27.13}, {-16.35, 135.64, 36.80}, {-38.50, 126.48, 36.42}, {-37.91, 127.36, 13.71}, {-16.71, 135.51, 12.83}, {-29.76, 177.69, 40.50}, {-53.35, 167.89, 40.74}, {-53.55, 167.78, 14.73}, {-29.53, 177.76, 14.96} },
{ {-139.75, 87.25, 27.13}, {-107.47, 84.35, 36.80}, {-116.66, 62.21, 36.42}, {-116.86, 63.25, 13.71}, {-107.64, 84.01, 12.83}, {-146.69, 104.60, 40.50}, {-156.44, 80.99, 40.74}, {-156.50, 80.77, 14.73}, {-146.58, 104.81, 14.96} },
{ {-160.51, -37.12, 27.13}, {-135.64, -16.35, 36.80}, {-126.48, -38.50, 36.42}, {-127.36, -37.91, 13.71}, {-135.51, -16.71, 12.83}, {-177.69, -29.76, 40.50}, {-167.89, -53.35, 40.74}, {-167.78, -53.55, 14.73}, {-177.76, -29.53, 14.96} },
{ {-87.25, -139.75, 27.13}, {-84.35, -107.47, 36.80}, {-62.21, -116.66, 36.42}, {-63.25, -116.86, 13.71}, {-84.01, -107.64, 12.83}, {-104.60, -146.69, 40.50}, {-80.99, -156.44, 40.74}, {-80.77, -156.50, 14.73}, {-104.81, -146.58, 14.96} },
{ {37.12, -160.51, 27.13}, {16.35, -135.64, 36.80}, {38.50, -126.48, 36.42}, {37.91, -127.36, 13.71}, {16.71, -135.51, 12.83}, {29.76, -177.69, 40.50}, {53.35, -167.89, 40.74}, {53.55, -167.78, 14.73}, {29.53, -177.76, 14.96} },
{ {139.75, -87.25, 27.13}, {107.47, -84.35, 36.80}, {116.66, -62.21, 36.42}, {116.86, -63.25, 13.71}, {107.64, -84.01, 12.83}, {146.69, -104.60, 40.50}, {156.44, -80.99, 40.74}, {156.50, -80.77, 14.73}, {146.58, -104.81, 14.96} },
{ {134.26, 26.25, -95.72}, {124.08, 11.56, -67.01}, {114.67, 33.61, -67.30}, {100.55, 26.81, -83.76}, {108.28, 5.43, -83.98}, {156.64, 21.05, -95.49}, {147.01, 44.70, -95.31}, {129.91, 37.87, -113.68}, {140.03, 13.91, -113.54} },
{ {-26.25, 134.26, -95.72}, {-11.56, 124.08, -67.01}, {-33.61, 114.67, -67.30}, {-26.81, 100.55, -83.76}, {-5.43, 108.28, -83.98}, {-21.05, 156.64, -95.49}, {-44.70, 147.01, -95.31}, {-37.87, 129.91, -113.68}, {-13.91, 140.03, -113.54} },
{ {-134.26, -26.25, -95.72}, {-124.08, -11.56, -67.01}, {-114.67, -33.61, -67.30}, {-100.55, -26.81, -83.76}, {-108.28, -5.43, -83.98}, {-156.64, -21.05, -95.49}, {-147.01, -44.70, -95.31}, {-129.91, -37.87, -113.68}, {-140.03, -13.91, -113.54} },
{ {26.25, -134.26, -95.72}, {11.56, -124.08, -67.01}, {33.61, -114.67, -67.30}, {26.81, -100.55, -83.76}, {5.43, -108.28, -83.98}, {21.05, -156.64, -95.49}, {44.70, -147.01, -95.31}, {37.87, -129.91, -113.68}, {13.91, -140.03, -113.54} }
};









