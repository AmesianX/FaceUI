#include "stdafx.h"

namespace Face
{
	Point::Point()
	{
		x = y = 0;
	}

	Point::Point(const POINT& src)
	{
		x = src.x;
		y = src.y;
	}

	Point::Point(int _x, int _y)
	{
		x = _x;
		y = _y;
	}

	Point::Point(LPARAM lParam)
	{
		x = GET_X_LPARAM(lParam);
		y = GET_Y_LPARAM(lParam);
	}

	///////////////////////////////////////////////////
	Size::Size()
	{
		cx = cy = 0;
	}

	Size::Size(const SIZE& src)
	{
		cx = src.cx;
		cy = src.cy;
	}

	Size::Size(const RECT rc)
	{
		cx = rc.right - rc.left;
		cy = rc.bottom - rc.top;
	}

	Size::Size(int _cx, int _cy)
	{
		cx = _cx;
		cy = _cy;
	}

	///////////////////////////////////////////////////
	Rect::Rect()
	{
		left = top = right = bottom = 0;
	}

	Rect::Rect(const RECT& src)
	{
		left = src.left;
		top = src.top;
		right = src.right;
		bottom = src.bottom;
	}

	Rect::Rect(int iLeft, int iTop, int iRight, int iBottom)
	{
		left = iLeft;
		top = iTop;
		right = iRight;
		bottom = iBottom;
	}

	int Rect::GetWidth() const
	{
		return right - left;
	}

	int Rect::GetHeight() const
	{
		return bottom - top;
	}

	void Rect::Empty()
	{
		left = top = right = bottom = 0;
	}

	bool Rect::IsNull() const
	{
		return (left == 0 && right == 0 && top == 0 && bottom == 0);
	}

	void Rect::Join(const RECT& rc)
	{
		if (rc.left < left) left = rc.left;
		if (rc.top < top) top = rc.top;
		if (rc.right > right) right = rc.right;
		if (rc.bottom > bottom) bottom = rc.bottom;
	}

	void Rect::ResetOffset()
	{
		::OffsetRect(this, -left, -top);
	}

	void Rect::Normalize()
	{
		if (left > right) { int iTemp = left; left = right; right = iTemp; }
		if (top > bottom) { int iTemp = top; top = bottom; bottom = iTemp; }
	}

	void Rect::Offset(int cx, int cy)
	{
		::OffsetRect(this, cx, cy);
	}

	void Rect::Inflate(int cx, int cy)
	{
		::InflateRect(this, cx, cy);
	}

	void Rect::Deflate(int cx, int cy)
	{
		::InflateRect(this, -cx, -cy);
	}

	void Rect::Union(Rect& rc)
	{
		::UnionRect(this, this, &rc);
	}
}