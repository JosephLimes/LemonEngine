#include "SpriteFont.h"

#include <xmllite.h>
#include <shlwapi.h>

#include "Asset Management/TextureManager.h"
#include "Asset Management/ImageManager.h"
#include "Sprite.h"

SpriteFont::SpriteFont(std::string path)
{
	m_name = path;

	// <Load associated texture into TextureManager>
	TextureManager::Load(path, "../Fonts/" + path + ".tga");
	m_pTexture = TextureManager::Get(path);

	// Parse associated XML file
	XMLtoCollection("Fonts/" + path + ".xml");

	// Manually add \t character
	AddCharToMap(9, 0.0f, 0.0f, 4.0f * GetGlyph(32)->GetWidth(), 1.0f);
}

SpriteFont::~SpriteFont()
{
	for (std::pair<int, Glyph*> entry : m_fontmap)
	{
		delete entry.second;
	}
}

void SpriteFont::XMLtoCollection(std::string filename)
{
	IXmlReader* reader = nullptr;
	IStream* readStream = nullptr;
	XmlNodeType nodeType;

	CreateXmlReader(IID_PPV_ARGS(&reader), nullptr);

	SHCreateStreamOnFile(filename.c_str(), STGM_READ, &readStream);

	reader->SetProperty(XmlReaderProperty_DtdProcessing, DtdProcessing_Prohibit);
	reader->SetInput(readStream);

	const wchar_t* stringValue = nullptr;
	unsigned int stringSize = 0;

	int key = 0;	// ASCII value
	int x = 0;		// x, y position of the glyph in texture
	int y = 0;
	int w = 0;		// width and height of the gluth in texture
	int h = 0;

	while (S_OK == reader->Read(&nodeType))
	{
		switch (nodeType)
		{
		case XmlNodeType::XmlNodeType_Element:
		{
			reader->GetQualifiedName(&stringValue, &stringSize);

			if (wcscmp(stringValue, L"character") == 0)
			{
				//Gets ASCII value
				reader->MoveToAttributeByName(L"key", nullptr);
				reader->GetValue(&stringValue, &stringSize);
				key = _wtoi(stringValue);
			}
			else if (wcscmp(stringValue, L"x") == 0)
			{
				ElementTextToInt(reader, x);
			}
			else if (wcscmp(stringValue, L"y") == 0)
			{
				ElementTextToInt(reader, y);
			}
			else if (wcscmp(stringValue, L"width") == 0)
			{
				ElementTextToInt(reader, w);
			}
			else if (wcscmp(stringValue, L"height") == 0)
			{
				ElementTextToInt(reader, h);
			}
			else
			{
			}
		} break;

		case XmlNodeType::XmlNodeType_EndElement:
		{
			reader->GetQualifiedName(&stringValue, &stringSize);
			assert(stringValue);

			//If we are at the end of "character", we found everything we need for this char
			if (wcscmp(stringValue, L"character") == 0)
			{
				//************************************************************************
				// You now have all the data for a character: key, x, y, w, h
				//
				// Load the associated image in the ImageManager 
				// (its name could be <font name><key> to insure uniqueness)
				//
				// Create the glyph and add it to the fontmap
				// NB: Consider moving the glyph's origin to the *upper-left* corner...
				//*************************************************************************

				//DebugMsg::out("Font %s: creating glyph for ASCII %i\n", m_name.c_str(), key);

				AddCharToMap(key, float(x), float(y), float(w), float(h));
			}

		} break;

		//Don't care about these
		case XmlNodeType::XmlNodeType_Attribute:
		case XmlNodeType::XmlNodeType_CDATA:
		case XmlNodeType::XmlNodeType_Comment:
		case XmlNodeType::XmlNodeType_DocumentType:
		case XmlNodeType::XmlNodeType_None:
		case XmlNodeType::XmlNodeType_ProcessingInstruction:
		case XmlNodeType::XmlNodeType_Text:
		case XmlNodeType::XmlNodeType_Whitespace:
		case XmlNodeType::_XmlNodeType_Last:
		default:
		{} break;
		}
	}

	//Release COM objects
	if (readStream)
	{
		readStream->Release();
	}

	if (reader)
	{
		reader->Release();
	}
}

void SpriteFont::ElementTextToInt(IXmlReader* pReader, int& out)
{
	const wchar_t* stringValue = nullptr;
	UINT stringSize = 0;
	XmlNodeType nodeType;

	while (S_OK == pReader->Read(&nodeType))
	{
		if (nodeType == XmlNodeType::XmlNodeType_Text)
		{
			pReader->GetValue(&stringValue, &stringSize);
			assert(stringValue);

			out = _wtoi(stringValue);
			break;
		}
	}
}

void SpriteFont::AddCharToMap(int key, float x, float y, float w, float h)
{
	std::string id = m_name + "_" + std::to_string(key);

	ImageManager::Load(id, m_pTexture, new Rect(x, y, w, h));

	Glyph* pGlyph = new Glyph(id);
	pGlyph->SetCenter(0.0f, 0.0f);

	m_fontmap.insert({ key, pGlyph });
}

SpriteFont::Glyph* SpriteFont::GetGlyph(char c)
{
	return m_fontmap[int(c)];
}

float SpriteFont::GetHeight()
{
	// kind of hacky, grab height of 'I' and set that as height
	// this prevents tab character (height of 1) potentially representing whole font height
	return GetGlyph(74)->GetHeight();
}
