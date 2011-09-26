#include "precompile.h"
#include "aki/image.h"

#if SR_WIN
#include "aki/image_loader_soil.h"
#elif
#error "not support"
#endif


namespace aki
{
	ImageDescription::ImageDescription()
		: width_(0), 
		height_(0),
		internal_format_(kInternalFormatRGBA),
		pixel_type_(kPixelType8888)
	{
	}
	ImageDescription::ImageDescription(int width, int height, InternalFormat internal_format, PixelType pixel_type)
		: width_(width),
		height_(height),
		internal_format_(internal_format),
		pixel_type_(pixel_type)
	{
	}
	ImageDescription::~ImageDescription()
	{
	}
	int ImageDescription::get_width() const
	{
		return width_;
	}
	int ImageDescription::get_height() const
	{
		return height_;
	}

	InternalFormat ImageDescription::get_internal_format() const
	{
		return internal_format_;
	}
	PixelType ImageDescription::get_pixel_type() const
	{
		return pixel_type_;
	}

	int ImageDescription::GetPixelSize() const
	{
		int pixel_size = 0;
		switch(get_pixel_type()) {
		case kPixelType8888:
			pixel_size = 4;	//4byte
			break;
		case kPixelType5551:
			pixel_size = 2;
			break;
		case kPixelType4444:
			pixel_size = 2;
			break;
		case kPixelType565:
			pixel_size = 2;
			break;
		default:
			SR_ASSERT(!"not valid");
		}
		return pixel_size;
	}
	int ImageDescription::GetRowLineSize() const
	{
		int pixel_size = GetPixelSize();
		int linesize = pixel_size * width_;
		return linesize;
	}
	bool ImageDescription::operator==(const ImageDescription &o) const
	{
		return (width_ == o.width_
			&& height_ == o.height_
			&& internal_format_ == o.internal_format_
			&& pixel_type_ == o.pixel_type_);
	}
	bool ImageDescription::operator!=(const ImageDescription &o) const
	{
		return !(*this == o);
	}
	/////////////////////////////////
	ImagePtr Image::create(const std::string &path)
	{
#if SR_WIN
		//use soil
		return ImageLoader_SOIL::load(path);
#elif _IPHONE_
#error "not support"
		//use core graphic
#endif
	}
	Image::Image(const ImageDescription &desc, void *data)
		: desc_(desc), data_(data)
	{
	}
	Image::Image(int width, int height)
		: data_(NULL)
	{
		desc_ = ImageDescription(width, height, kInternalFormatRGBA, kPixelType8888);
		data_ = malloc(sizeof(unsigned char) * 4 * width * height);
		memset(data_, 0, sizeof(unsigned char) * 4 * width * height);
	}
	Image::~Image()
	{
		free(data_);
		data_ = NULL;
	}
	const ImageDescription &Image::get_desc() const
	{
		return desc_;
	}
	const void *Image::get_data() const
	{
		return data_;
	}
	void Image::Overwrite(const Image &o)
	{
		//������ �����Ҷ��� ����Ⱑ �����ϰ�����
		//���� ������ �ٸ����� ����⸦ ������ ���� �������� �ڵ�󿡼� ����������
		//�����Ű����ϱ� ���߿� �߰�����
		SR_ASSERT(desc_.get_internal_format() == o.get_desc().get_internal_format()
			&& desc_.get_pixel_type() == o.get_desc().get_pixel_type());
		//�ؽ��� ũ�� �������ε� �� ���� �̹����� ����� ���� �������̴�
		SR_ASSERT(desc_.get_width() >= o.get_desc().get_width()
			&& desc_.get_height() >= o.get_desc().get_height());

		//�ٴ����� �����ϱ�
		for(int y = 0 ; y < o.get_desc().get_height() ; y++)
		{
			int prev_index = o.GetPixelIndex(0, y);
			int curr_index = GetPixelIndex(0, y);
			unsigned char *prev_data = (unsigned char*)o.get_data();
			unsigned char *curr_data = (unsigned char*)get_data();

			unsigned char *src = prev_data + prev_index;
			unsigned char *dst = curr_data + curr_index;

			int rowline = o.get_desc().GetRowLineSize();
			memcpy(dst, src, rowline);
		}
	}
	int Image::GetPixelIndex(int x, int y) const
	{
		int width = desc_.get_width();
		int height = desc_.get_height();
		SR_ASSERT(x >= 0 && x < width && y >= 0 && y < height);
		int pixel_size = desc_.GetPixelSize();
		int linesize = desc_.GetRowLineSize();
		return (linesize * y) + (pixel_size * x);
	}

	bool Image::operator==(const Image &o) const
	{
		if(desc_ != o.desc_)
		{
			return false;
		}
		int size = desc_.get_height() * desc_.GetRowLineSize();
		if(memcmp(data_, o.data_, size) == 0)
		{
			return true;
		}
		return false;
	}
	bool Image::operator!=(const Image &o) const
	{
		return !(*this == o);
	}
}