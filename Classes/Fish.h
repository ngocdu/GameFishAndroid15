//
//  Fish.h
//  GameFish
//
//  Created by MinhNT on 13/08/05.
//
//

#ifndef GameFish_Fish_h
#define GameFish_Fish_h
#include <string.h>
#include "cocos2d.h"
#include "SimpleAudioEngine.h"
using namespace std;
using namespace cocos2d;
class Fish : public cocos2d::CCSprite
{
private :    
    CC_SYNTHESIZE(string , _name, Name);
    CC_SYNTHESIZE(bool , _isPlayer, IsPlayer);
    // = false nếu không bị trúng  độc   ; = true nếu trúng độc
    CC_SYNTHESIZE(bool , _trungDoc, TrungDoc);
    CC_SYNTHESIZE(bool , _dingMuc, DinhMuc);
    //thuoc tinh moc gai nay chi danh cho cac con ca Gai
    CC_SYNTHESIZE(bool, _mocGai, MocGai);
    //==true neu cham vao con ca dang moc gai
    CC_SYNTHESIZE(bool, _chamPhaiCaGai, ChamPhaiCaGai);
    CC_SYNTHESIZE(int, _point, Point);
    //so nay la so hoa sang ma con ca an duoc de tang ban kinh vong sang
    CC_SYNTHESIZE(int, _soHoaSangAnDuoc, SoHoaSangAnDuoc);
    // =0 neu di chueyn sang trai , =1 neu di chueyn sang phai
    CC_SYNTHESIZE(int, _huongDiChuyen, HuongDiChuyen);
    // so nay cang lon thi cang thong minh tuy thuoc vao tung loai thong minh ta se tao cac hanh dong phu hop
    // ta co the cho chi so nay random hoac gan cho tung loai ca
    // cai nay chinh la cai de chung ta cho con ca nay gap con ca to hon thi chay hay la khong
    /* neu chi so thong minh : 0 - cha biet gi chi biet boi loang quoang gap ca  to cung k biet
     1 - biet chay di cho khac khi gap ca to hon neu nguoc chieu di chuyen cua no
     2 - biet chay di khi lai gan ca to
     3 - biet chay khi gap ca to va duoi theo ca be
     */
    CC_SYNTHESIZE(int, _chiSoThongMinh, ChiSoThongMinh);
    // van toc di chuyen cua con ca (moi loai ca se co van toc di chuyen khac nhau )
    CC_SYNTHESIZE(int, _vanToc, VanToc);
    CC_SYNTHESIZE(int, _soLanChayTron, SoLanChayTron);
    CC_SYNTHESIZE(int, _nhom, Nhom);
    CC_SYNTHESIZE(int, _themMang, ThemMang);
    //so anh tao animation boi dung
    CC_SYNTHESIZE(int, _numberImage, NumberImage);
    // = true neu con ca chinh an duoc cai qua cau lam cho cac con ca khac dung lai
    CC_SYNTHESIZE(bool, _choang, Choang);
    //gan cai anh nay vao duoi con ca chinh sau nay con ca chinh doi chieu thi
    //ta quay cai anh nay 180 do de luon biet dau la duoi con ca chinh
    CC_SYNTHESIZE(CCPoint , _head, Head);
    CC_SYNTHESIZE(CCPoint , _tails, Tails);
    CC_SYNTHESIZE(CCPoint , _viTri, ViTri);
public:
    // constructor -- ham tao
	Fish();
	Fish(string _name, int _point);// ham tao co doi so
    void diChuyen();
    void boiDung();
    void dopMoi();
    void startBoiDung(CCNode * node);
};
#endif
