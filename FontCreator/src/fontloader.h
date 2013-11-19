/**
 * フォント読み込みクラスの定義.
 * @file fontloader.h.
 * @author yatagai.
 */
#include <ft2build.h>
#include FT_FREETYPE_H
#include <vector>
#include <QPainterPath>

namespace font_creator
{

/**
 *  フォント読み込みクラス.
 *  @author yatagai.
 */
class FontLoader
{
public:
    struct FontBitmap {
        FontBitmap()
            : bitmap(nullptr)
            , width(0.0f)
            , height(0.0f)
            , offset_y(0.0f)
        {}
        ~FontBitmap()
        {
            if (bitmap)
            {
                delete[] bitmap;
                bitmap = nullptr;
            }
        }

        void *bitmap;
        float width;
        float height;
        float offset_y;
    };

    struct FontInfo {
        FontInfo()
            : charactor(0)
            , has_outline(false)
            , width(0.0f)
            , bearing_x(0.0f)
            , fill()
        {}
        ~FontInfo()
        {}

        bool operator <(const FontInfo &cmp)
        {
            return charactor < cmp.charactor;
        }

        char32_t charactor;

        bool has_outline;
        float width;
        float bearing_x;
        QPainterPath path;

        FontBitmap fill;
    };
public:
    struct CreateParam
    {
        unsigned int font_size; // fontサイズ(pixel).
        float out_line_width;   // 輪郭線太さ(pixel).
        bool out_line;
    };

public:
    explicit FontLoader();
    ~FontLoader();
    bool Load(const char *file_name, int face_index = 0);
    bool CreateFontInfo(const char16_t *text, const CreateParam &param);
    unsigned int GetFontInfoCount() const;
    const FontInfo& GetFontInfo(unsigned int index) const;
    bool CanRenderCharactor(const char16_t text);
    bool HasFace() const;

    int HasFamily(const char *file_name, QString &family_name);
private:
    FT_Library m_library;
    FT_Face m_face;
    FT_GlyphSlot m_slot;
    FT_UInt m_glyph_index;
    CreateParam m_create_param;
    // フォント情報.
public:
    float GetMaxFontHeight() const
    {
        return m_max_ascend + m_max_dscend + 1.0f;
    }
    float GetMaxAscend() const
    {
        return m_max_ascend;
    }
    float GetMaxDscend() const
    {
        return m_max_dscend;
    }
private:
    bool CreateFontInfoCache(const char16_t *text);
    void DestroyFontInfoCache();
    void DoneFace();
private:
    std::vector<FontInfo> m_font_info_cache;
    float m_max_ascend;
    float m_max_dscend;
};
}   // namespace font_creator.
