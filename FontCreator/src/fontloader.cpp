/**
 * フォント読み込みクラスの実装.
 * @file fontloader.cpp.
 * @author yatagai.
 */
#include "fontloader.h"
#include FT_OUTLINE_H
#include FT_BITMAP_H
#include FT_STROKER_H
#include "freetype/internal/ftmemory.h"
#include "freetype/ftsnames.h"
#include <algorithm>
#include <functional>
#include <assert.h>

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

int MoveTo(const FT_Vector *to, void *user)
{
    QPainterPath *path = reinterpret_cast<QPainterPath *>(user);
    path->moveTo(to->x / 64.0f, -to->y / 64.0f);
    return 0;
}

int LineTo(const FT_Vector *to, void *user)
{
    QPainterPath *path = reinterpret_cast<QPainterPath *>(user);
    path->lineTo(to->x / 64.0f, -to->y / 64.0f);
    return 0;
}

int ConicTo(const FT_Vector *control, const FT_Vector *to, void *user)
{
    QPainterPath *path = reinterpret_cast<QPainterPath *>(user);
    path->quadTo(control->x / 64.0f, -control->y / 64.0f,
                    to->x / 64.0f, -to->y / 64.0f);
    return 0;
}

int CubicTo(const FT_Vector *control1, const FT_Vector *control2, const FT_Vector *to, void *user)
{
    QPainterPath *path = reinterpret_cast<QPainterPath *>(user);
    path->cubicTo(control1->x / 64.0f, -control1->y / 64.0f,
                    control2->x / 64.0f, -control2->y / 64.0f,
                    to->x / 64.0f, -to->y / 64.0f);
    return 0;
}

FT_Outline_Funcs g_ft_outline_funcs =
{
    MoveTo,
    LineTo,
    ConicTo,
    CubicTo,
    0,
    0
};
}   // namespace.

/**
 * @brief コンストラクタ.
 */
FontLoader::FontLoader() :
  m_library(nullptr)
, m_face(nullptr)
, m_font_info_cache()
, m_max_ascend(0.0f)
, m_max_dscend(0.0f)
{
    std::memset(&m_create_param, 0, sizeof(m_create_param));
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
 * @param face_index フェイスインデックス.
 * @return trueで読み込み成功 falseで読み込み失敗.
 */
bool FontLoader::Load(const char *file_name, int face_index)
{
    DoneFace();

    // init face.
    FT_Error error = FT_New_Face(m_library, file_name, face_index, &m_face);
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
 * @param create_param フォント生成情報.
 * @return trueで作成成功 falseで作成失敗.
 */
bool FontLoader::CreateFontInfo(const char16_t *text, const CreateParam &create_param)
{
    // set font size.
    FT_Error error = FT_Set_Pixel_Sizes(m_face, 0, create_param.font_size);
    if (error)
    {
        // return false;
    }
    std::memcpy(&m_create_param, &create_param, sizeof(create_param));
    return CreateFontInfoCache(text);
}

/**
 * @brief フォント情報の数を取得.
 * @return フォント情報の数.
 */
unsigned int FontLoader::GetFontInfoCount() const
{
    return static_cast<unsigned int>(m_font_info_cache.size());
}

/**
 * @brief フォント情報取得.
 * @param index 取得する文字のインデックス.
 * @return フォント情報 nullptrで取得失敗.
 */
const FontLoader::FontInfo& FontLoader::GetFontInfo(unsigned int index) const
{
    assert(m_font_info_cache.size() > index);
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
        if (text[i] == '\r' || text[i] == '\n')
        {
            continue;
        }
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
    size_t bitmap_size = 0;
    // float base_line_height = m_face->size->metrics.ascender / 64.0f;
    m_max_ascend = 0.0f;
    m_max_dscend = 0.0f;
    for (; it != m_font_info_cache.end();)
    {
        FontInfo &info = (*it);
        FT_Load_Char(m_face, static_cast<FT_ULong>(info.charactor), FT_LOAD_NO_BITMAP);
        // 輪郭線が生成可能ならパスを生成.
        if (m_face->glyph->format == FT_GLYPH_FORMAT_OUTLINE) {
            info.has_outline = true;
            FT_Glyph ft_glyph;
            FT_Get_Glyph(m_face->glyph, &ft_glyph);
            FT_Outline_Decompose(&m_slot->outline, &g_ft_outline_funcs, &info.path);
            FT_Done_Glyph(ft_glyph);
        }
        else
        {
            // ビットマップフォント作成.
            if (m_slot->format == FT_GLYPH_FORMAT_OUTLINE)
            {
                FT_Outline_Embolden(&m_slot->outline, 0);
            }
            FT_Render_Glyph(m_slot, FT_RENDER_MODE_NORMAL);
            info.fill.width = static_cast<float>(m_slot->bitmap.width);
            info.fill.height = static_cast<float>(m_slot->bitmap.rows);
            // info.fill.offset_y = std::ceilf(base_line_height - static_cast<float>(m_slot->bitmap_top));
            info.fill.offset_y = 0; // bitmapフォントは0でいいはず.
            bitmap_size = static_cast<size_t>(info.fill.width * info.fill.height);
            info.fill.bitmap = new unsigned char[bitmap_size];
            if (m_slot->bitmap.pixel_mode == FT_PIXEL_MODE_GRAY)
            {
                memcpy(info.fill.bitmap, m_slot->bitmap.buffer, bitmap_size);
            }
            else if (m_slot->bitmap.pixel_mode == FT_PIXEL_MODE_MONO)
            {
                if (bitmap_size > 0)
                {
                    int temp = 0;
                    for (int index_dest = 0, index_src = 0;;)
                    {
                        for (int bit = 0; bit < 8; ++bit)
                        {
                            ((unsigned char *)info.fill.bitmap)[index_dest++] = (((unsigned char *)m_slot->bitmap.buffer)[index_src + temp] & (0x80) >> bit) ? 255 : 0;
                            if (index_dest % (int)info.fill.width == 0)
                            {
                                temp = -1;
                                index_src += m_slot->bitmap.pitch;
                                break;
                            }
                        }
                        if (index_dest >= info.fill.width * info.fill.height)
                        {
                            break;
                        }
                        ++temp;
                    }
                }
            }
        }

        // サイズ代入.
        info.width = m_slot->metrics.width / 64.0f;
        info.bearing_x = m_slot->metrics.horiBearingX / 64.0f;
        if (m_slot->metrics.horiBearingY > m_max_ascend)
        {
           m_max_ascend = m_slot->metrics.horiBearingY;
        }
        if (m_slot->metrics.height - m_slot->metrics.horiBearingY - 1.0f >= m_max_dscend)
        {
            m_max_dscend = m_slot->metrics.height - m_slot->metrics.horiBearingY - 1.0f;
        }
        ++it;
    }
    m_max_ascend /= 64.0f;
    m_max_dscend /= 64.0f;

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

/**
 * @brief ファミリーを持っているか.
 * @param file_name ファイル名.
 * @param family_name ファミリー名.
 * @return Faceインデックス.
 */
int FontLoader::HasFamily(const char *file_name, QString &family_name)
{
    FT_Face serach_face;
    int face_index = 0;
    while (FT_New_Face(m_library, file_name, face_index, &serach_face) == 0)
    {
        QString face_family_name = serach_face->family_name;
        bool find = family_name == face_family_name;
        if (!find)
        {
            int name_count = FT_Get_Sfnt_Name_Count(serach_face);
            char temp[256] = {0};
            char16_t temp16[256] = {0};
            FT_SfntName name;
            for (int i = 0; i < name_count && !find; ++i)
            {
                if (FT_Get_Sfnt_Name(serach_face, i, &name) != 0)
                {
                    break;
                }
                // ファミリ名以外は飛ばす.
                if (name.name_id != 4)
                {
                    continue;
                }
                if (name.encoding_id == 0)
                {
                    assert(name.string_len < 256);
                    std::memcpy(temp, name.string, name.string_len);
                    temp[name.string_len] = '\0';
                    face_family_name = temp;
                }
                else if (name.encoding_id == 1)
                {
                    assert(name.string_len < 256 * 2);
                    std::memcpy(&temp16, name.string, name.string_len);
                    temp16[name.string_len / 2] = '\0';
                    // ビッグエンディアンで格納されている.
                    for (unsigned int j = 0; j < name.string_len / 2; ++j)
                    {
                        char *bit8 = reinterpret_cast<char *>(&temp16[j]);
                        char bit8_temp = bit8[1];
                        bit8[1] = bit8[0];
                        bit8[0] = bit8_temp;
                    }
                    face_family_name.setUtf16(temp16, name.string_len / 2);
                }
                find |= family_name == face_family_name;
            }
        }
        FT_Done_Face(serach_face);
        if (find)
        {
            return face_index;
        }
        ++face_index;
    }
    return -1;
}

}   // namespace font_crator.
