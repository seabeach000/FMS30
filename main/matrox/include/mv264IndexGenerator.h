#include <iostream>
#include <fstream>

#ifndef LINUX_PLATFORM
class C264Index
{
public:
   C264Index::C264Index(uint64_t in_ui64Position, uint64_t in_ui64DisplayPosition, uint64_t in_ui64CodedPosition, uint64_t in_ui64Size, uint32_t in_ui32Type, std::string in_strType)
      : m_ui64Position(in_ui64Position)
      , m_ui64DisplayPosition(in_ui64DisplayPosition)
      , m_ui64CodedPosition(in_ui64CodedPosition)
      , m_ui64Size(in_ui64Size)
      , m_ui32Type(in_ui32Type)
      , m_strType(in_strType)
   {
   }


   std::string C264Index::GetString() const
   {
      char szString[MAXSIZE];
      std::string str;

      sprintf_s(szString, MAXSIZE, "%" PRIu64 ",%" PRIu64 ",%" PRIu64 ",%" PRIu64 ",%d,%s", m_ui64Position, m_ui64DisplayPosition, m_ui64CodedPosition, m_ui64Size, m_ui32Type, m_strType.c_str());

      str = szString;

      return str;
   }

   operator std::string() const { return GetString(); }

protected:
   uint64_t          m_ui64Position;
   uint64_t          m_ui64DisplayPosition;
   uint64_t          m_ui64CodedPosition;
   uint64_t          m_ui64Size;
   uint32_t          m_ui32Type;
   std::string       m_strType;

private:
   static const int MAXSIZE = 256; //definition
};

class C264IndexGenerator
{
public:
   C264IndexGenerator()
      : m_ui64Position(0)
      , m_ui8FieldCount(0)
      , m_bIsFieldType(false)
   {
   }

   void Reset()
   {
      m_ui64Position = 0;
      m_ui8FieldCount = 0;
      m_oDequeIndexes.clear();
   }

   bool DumpToFile(std::wstring in_wstrIndexFilename, uint32_t in_ui32Width, uint32_t in_ui32Height, std::string in_strFrameRate, std::string in_strScanMode, std::string in_strAspectRatio, uint32_t in_ui32BitCount)
   {
      try
      {
         std::ofstream  oIndexFile;
         oIndexFile.open(in_wstrIndexFilename);
         oIndexFile << ".264.index file" << std::endl << "Version 1.0" << std::endl;
         oIndexFile << "width=" << in_ui32Width << ",height=" << in_ui32Height << ",framerate=" << in_strFrameRate << ",scanmode=" << in_strScanMode << ",aspectratio=" << in_strAspectRatio << ",bitcount=" << in_ui32BitCount << ((m_bIsFieldType == true) ? ",Field" : ",Frame") << std::endl;
         oIndexFile << "framenumber=" << ((m_bIsFieldType == true) ? int(m_oDequeIndexes.size())/2 : int(m_oDequeIndexes.size()))  << std::endl;
         oIndexFile << "offset,display order,encoded order,size,type(int),type(str)" << std::endl;
         std::deque<C264Index>::iterator  iter = m_oDequeIndexes.begin();
         while (iter != m_oDequeIndexes.end())
         {
            oIndexFile << std::string(*iter);
            oIndexFile << std::endl;
            iter++;
         }
         oIndexFile.close();
      }
      catch (...)
      {
      }

      Reset();

      return true;
   }

   bool Add(bool in_bField, uint64_t in_ui64DisplayPosition, uint64_t in_ui64CodedPosition, uint64_t in_ui64Size, uint32_t  in_ui32Type, std::string in_strType)
   {
      m_bIsFieldType = in_bField;

      C264Index   o264Index(m_ui64Position, in_ui64DisplayPosition, in_ui64CodedPosition, in_ui64Size, in_ui32Type, in_strType);
      m_oDequeIndexes.push_back(o264Index);

      m_ui64Position += in_ui64Size;

      return true;
   }

private:
   uint64_t                                  m_ui64Position;
   uint8_t                                   m_ui8FieldCount;
   std::deque<C264Index>                     m_oDequeIndexes;

   uint64_t                                  m_ui64DisplayPosition;
   uint64_t                                  m_ui64CodedPosition;
   uint64_t                                  m_ui64Size;
   uint32_t                                  m_ui32Type;
   std::string                               m_strType;
   bool                                      m_bIsFieldType;

};
#endif
