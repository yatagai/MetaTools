/**
 * フォント読み込みクラスの実装.
 * @file fontloader.cpp.
 * @author yatagai.
 */
#include "fontloader.h"
#include <algorithm>
#include <functional>

namespace font_creator
{
namespace
{
/**
 * @brief FontLoader::FontInfo Unique比較.
 * @param left 比較対象左辺.
 * @param right 比較対象右辺.
 * @return trueで同じ文字 falseで違う文字.
 */
bool is_eqals_for_unique(const FontLoader::FontInfo &left,
                         const FontLoader::FontInfo &right)
{
  return (left.charactor == right.charactor);
}

}   // namespace.

/**
 * @brief コンストラクタ.
 */
FontLoader::FontLoader() :
  m_library(nullptr)
, m_face(nullptr)
, m_font_info_cache()
, m_font_size(0)
{
    FT_Init_FreeType(&m_library);
}

/**
 * @brief デストラクタ.
 */
FontLoader::~FontLoader()
{
    DestroyFontInfoCache();
    DoneFace();
    if(m_library)
    {
        FT_Done_FreeType(m_library);
    }
}

/**
 * @brief 読み込み.
 * @param file_name フォントファイル名.
 * @return trueで読み込み成功 falseで読み込み失敗.
 */
bool FontLoader::Load(const char *file_name)
{
    DoneFace();

    // init face.
    FT_Error error = FT_New_Face(m_library, file_name, 0, &m_face);
    if (error)
    {
        return false;
    }
    m_slot = m_face->glyph;
    return true;
}

/**
 * @brief フォント情報作成.
 * @param text 作成するテキスト.
 * @param font_size フォントサイズ(ピクセル).
 * @return trueで作成成功 falseで作成失敗.
 */
bool FontLoader::CreateFontInfo(const char16_t *text, unsigned int font_size)
{
    // set font size.
    FT_Error error = FT_Set_Pixel_Sizes(m_face, 0, font_size);
    if (error)
    {
        return false;
    }
    m_font_size = font_size;
    return CreateFontInfoCache(text);
}

/**
 * @brief フォント情報の数を取得.
 * @return フォント情報の数.
 */
unsigned int FontLoader::GetFontInfoCount() const
{
    return m_font_info_cache.size();
}

/**
 * @brief フォント情報取得.
 * @param index 取得する文字のインデックス.
 * @return フォント情報 nullptrで取得失敗.
 */
const FontLoader::FontInfo& FontLoader::GetFontInfo(unsigned int index) const
{
    return m_font_info_cache[index];
}

/**
 * @brief 描画可能か.
 * @param text 判定する文字.
 * @return trueで描画可能 falseで描画不可能.
 */
bool FontLoader::CanRenderCharactor(const char16_t text)
{
    FT_Load_Char(m_face, static_cast<FT_ULong>(text), FT_LOAD_RENDER);
    return FT_Get_Char_Index(m_face, static_cast<FT_ULong>(text)) != 0 &&
             m_slot->metrics.width != 0;
}

/**
 * @brief faceを持っているか.
 * @return trueで持っている falseで持っていない.
 */
bool FontLoader::HasFace() const
{
    return m_face != nullptr;
}

/**
 * @brief フォント情報キャッシュ作成.
 * @param text 作成するテキスト.
 * @return trueで作成成功 falseで作成失敗.
 */
bool FontLoader::CreateFontInfoCache(const char16_t *text)
{
    // free old cache.
    DestroyFontInfoCache();

    // make list.
    FontInfo new_info;
    for (int i = 0;; ++i)
    {
        if (text[i] == 0)
        {
            break;
        }
        new_info.charactor = text[i];
        m_font_info_cache.push_back(new_info);
    }
    // sort and unique.
    std::sort(m_font_info_cache.begin(), m_font_info_cache.end());
    std::vector<FontInfo>::iterator new_end = std::unique(m_font_info_cache.begin(),
                                                      m_font_info_cache.end(),
                                                      is_eqals_for_unique);
    m_font_info_cache.erase(new_end, m_font_info_cache.end());

    std::vector<FontInfo>::iterator it = m_font_info_cache.begin();
    for (; it != m_font_info_cache.end(); ++it)
    {
        FontInfo &info = (*it);
        FT_Load_Char(m_face, static_cast<FT_ULong>(info.charactor), FT_LOAD_RENDER);
        info.width = static_cast<float>(m_slot->metrics.width) / 64;
        info.height = static_cast<float>(m_slot->metrics.height) / 64;
        info.offst_y = m_font_size - static_cast<float>(m_slot->metrics.horiBearingY) / 64;
        info.bitmap = new char[static_cast<size_t>(info.width * info.height)];
        memcpy(info.bitmap, m_slot->bitmap.buffer, static_cast<size_t>(info.width * info.height));
    }

    return true;
}

/**
 * @brief フォント情報キャッシュ破棄.
 */
void FontLoader::DestroyFontInfoCache()
{
    m_font_info_cache.clear();
}

/**
 * @brief フェイスの終了処理.
 */
void FontLoader::DoneFace()
{
    if (m_face)
    {
        FT_Done_Face(m_face);
        m_face = nullptr;
    }
}
}   // namespace font_crator.
