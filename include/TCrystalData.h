#ifndef TCRYSTALDATA_H
#define TCRYSTALDATA_H

#include <cstdlib>
#include <cstdio>
#include <vector>

#include "Globals.h"

#include <TObject.h>

class TCrystalData : public TObject {

	private:
		std::vector<UShort_t> fClover_Nbr;		//!
		std::vector<UShort_t> fCore_Nbr;		//!
		std::vector<Double_t> fCore_Eng;		//!
		std::vector<Int_t>    fCore_Chg;		//!
		std::vector<Double_t> fCore_TimeCFD;		//!
		std::vector<Double_t> fCore_TimeLED;		//!
		std::vector<Double_t> fCore_Time;		//!
		std::vector<std::vector<int> >fCore_Wave;	//!


		std::vector<UShort_t> fSeg_Clover_Nbr;		//!
		std::vector<UShort_t> fSeg_Core_Nbr;		//!
		std::vector<UShort_t> fSegment_Nbr;		//!
		std::vector<Double_t> fSegment_Eng;		//!
		std::vector<Int_t>    fSegment_Chg;		//!
		std::vector<Double_t> fSegment_TimeCFD;		//!
		std::vector<Double_t> fSegment_TimeLED;		//!
		std::vector<Double_t> fSegment_Time;		//!
		std::vector<std::vector<int> > fSegment_Wave;	//!

	public:
		TCrystalData();					//!
		virtual ~TCrystalData();			//!
		
		virtual void Clear(Option_t *opt = "");		//!
		virtual void Print(Option_t *opt = "");		//!

		inline void SetCloverNumber(const UShort_t &CloverNumber) {fClover_Nbr.push_back(CloverNumber);}//!
		inline void SetCoreNumber(const UShort_t  &CoreNumber)	{fCore_Nbr.push_back(CoreNumber);}	//!
		inline void SetCoreEnergy(const Double_t  &CoreEnergy)	{fCore_Eng.push_back(CoreEnergy);}	//!
		inline void SetCoreCharge(const Int_t &CoreCharge)	{fCore_Chg.push_back(CoreCharge);}	//!
		inline void SetCoreCFD(const Double_t &CoreTimeCFD)	{fCore_TimeCFD.push_back(CoreTimeCFD);}	//!	
		inline void SetCoreLED(const Double_t &CoreTimeLED)	{fCore_TimeLED.push_back(CoreTimeLED);}	//!	
		inline void SetCoreTime(const Double_t    &CoreTime)	{fCore_Time.push_back(CoreTime);}	//!
		
		inline void SetCoreWave(const std::vector<int> &CoreWave)	{fCore_Wave.push_back(CoreWave);} //!
	
		inline void SetCore(const UShort_t &CloverNbr, const UShort_t &CoreNbr, const Double_t &CrystalEnergy, const Int_t &CrystalCharge, const Double_t &CrystalTimeCFD,const Double_t &CrystalTimeLED,const Double_t &CrystalTime)	{
			SetCloverNumber(CloverNbr);
			SetCoreNumber(CoreNbr);
			SetCoreEnergy(CrystalEnergy);		
			SetCoreCharge(CrystalCharge);
			SetCoreCFD(CrystalTimeCFD);		
			SetCoreLED(CrystalTimeLED);		
			SetCoreTime(CrystalTime);		
		}	//!

		inline void SetSegCloverNumber(const UShort_t &CloverNumber)	{fSeg_Clover_Nbr.push_back(CloverNumber);}	//!
		inline void SetSegCoreNumber(const UShort_t &CoreNumber)	{fSeg_Core_Nbr.push_back(CoreNumber);}	//!
		inline void SetSegmentNumber(const UShort_t &SegmentNumber)	{fSegment_Nbr.push_back(SegmentNumber);}	//!
		inline void SetSegmentEnergy(const Double_t &SegmentEnergy)	{fSegment_Eng.push_back(SegmentEnergy);}	//!
		inline void SetSegmentCharge(const Int_t &SegementCharge)	{fSegment_Chg.push_back(SegementCharge);}	//!
		inline void SetSegmentCFD(const Double_t &SegmentTimeCFD)	{fSegment_TimeCFD.push_back(SegmentTimeCFD);}	//!
		inline void SetSegmentLED(const Double_t &SegmentTimeLED)	{fSegment_TimeLED.push_back(SegmentTimeLED);}	//!
		inline void SetSegmentTime(const Double_t &SegmentTime)		{fSegment_Time.push_back(SegmentTime);}		//!

		inline void SetSegmentWave(const std::vector<int> &SegWave)	{fSegment_Wave.push_back(SegWave);}		//!

		inline void SetSegment(const UShort_t &SegCloverNbr, const UShort_t &SegCoreNbr, const UShort_t &SegmentNumber,const Double_t &SegmentEnergy, const Int_t &SegmentCharge, const Double_t &SegmentTimeCFD,const Double_t &SegmentTimeLED,const Double_t &SegmentTime)	{
			SetSegCloverNumber(SegCloverNbr);
			SetSegCoreNumber(SegCoreNbr);
			SetSegmentNumber(SegmentNumber);
			SetSegmentEnergy(SegmentEnergy);
			SetSegmentCharge(SegmentCharge);
			SetSegmentCFD(SegmentTimeCFD);
			SetSegmentLED(SegmentTimeLED);
			SetSegmentTime(SegmentTime);
		}	//!

		inline UShort_t GetCloverNumber(const unsigned int &i)	{return fClover_Nbr.at(i);}	//!
		inline UShort_t GetCoreNumber(const unsigned int &i)	{return fCore_Nbr.at(i);}	//!
		inline Double_t GetCoreEnergy(const unsigned int &i)	{return fCore_Eng.at(i);}	//!
		inline Int_t    GetCoreCharge(const unsigned int &i)	{return fCore_Chg.at(i);}	//!
		inline Double_t GetCoreCFD(const unsigned int &i)	{return fCore_TimeCFD.at(i);}	//!
		inline Double_t GetCoreLED(const unsigned int &i)	{return fCore_TimeLED.at(i);}	//!	
		inline Double_t GetCoreTime(const unsigned int &i)	{return fCore_Time.at(i);}	//!

		inline std::vector<int> GetCoreWave(const unsigned int &i)	{return fCore_Wave.at(i);}	//!

		inline UShort_t GetSegCloverNumber(const unsigned int &i) {return fSeg_Clover_Nbr.at(i);} //!
		inline UShort_t GetSegCoreNumber(const unsigned int &i) {return fSeg_Core_Nbr.at(i);}   //!
		inline UShort_t GetSegmentNumber(const unsigned int &i)	{return fSegment_Nbr.at(i);}	//!
		inline Double_t GetSegmentEnergy(const unsigned int &i)	{return fSegment_Eng.at(i);}	//!
		inline Int_t    GetSegmentCharge(const unsigned int &i) {return fSegment_Chg.at(i);}	//!
		inline Double_t GetSegmentCFD(const unsigned int &i){return fSegment_TimeCFD.at(i);}//!
		inline Double_t GetSegmentLED(const unsigned int &i){return fSegment_TimeLED.at(i);}//!
		inline Double_t GetSegmentTime(const unsigned int &i)	{return fSegment_Time.at(i);}	//!
	
		inline std::vector<int> GetSegmentWave(const unsigned int &i) {return fSegment_Wave.at(i);} //!

		inline unsigned int GetCoreMultiplicity()		{return fCore_Nbr.size();}	//!
		inline unsigned int GetSegmentMultiplicity()		{return fSegment_Nbr.size();}	//!
		
		ClassDef(TCrystalData,0)  // TCloverData structure
};


#endif





