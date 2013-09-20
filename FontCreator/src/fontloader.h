/**
 * フォント読み込みクラスの定義.
 * @file fontloader.h.
 * @author yatagai.
 */
#include <ft2build.h>
#include FT_FREETYPE_H
#include <vector>

namespace font_creator
{

/**
 *  フォント読み込みクラス.
 *  @author yatagai.
 */
class FontLoader
{
public:
    struct FontInfo {
        FontInfo()
            : bitmap(nullptr)
            , width(0.0f)
            , height(0.0f)
            , offst_y(0.0f)
            , charactor(0)
        {}
        ~FontInfo()
        {
            if (bitmap)
            {
                delete[] bitmap;
                bitmap = nullptr;
            }
        }

        bool operator <(const FontInfo &cmp)
        {
          return charactor < cmp.charactor;
        }

        void *bitmap;
        float width;
        float height;
        float offst_y;
        char32_t charactor;
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
    bool Load(const char *file_name);
    bool CreateFontInfo(const char16_t *text, const CreateParam &param);
    unsigned int GetFontInfoCount() const;
    const FontInfo& GetFontInfo(unsigned int index) const;
    bool CanRenderCharactor(const char16_t text);
    bool HasFace() const;
private:
    FT_Library m_library;
    FT_Face m_face;
    FT_GlyphSlot m_slot;
    FT_UInt m_glyph_index;
    CreateParam m_create_param;
    // フォント情報キャッシュ.
private:
    bool CreateFontInfoCache(const char16_t *text);
    void DestroyFontInfoCache();
    void DoneFace();
private:
    std::vector<FontInfo> m_font_info_cache;
};
}   // namespace font_creator.
