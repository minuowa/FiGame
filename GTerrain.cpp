#include "GGameDemoHeader.h"
#include "GTerrain.h"
#include "GD9Device.h"
#include "GTexture.h"
#include "GBitmap.h"
#include "GHeightMap.h"
#include "GTerrainNode.h"
#include "GCamera.h"
#include "GGame.h"
#include "GText.h"


GTerrain::GTerrain ( )
{
    mRootLevel = 8;
    mCellWidth = 50;
    mLODFactor = 800.f;
    mHeightMax = 700.0f;
    mHeightMin = -300.0f;
    mDisplayRepairAreaOnly = false;
    mFileHeightMap = "..\\Res\\Terrain\\heightmap.bmp";
    mHeightMap = nullptr;
    mRootNode = nullptr;
    mLODMode = true;
    ReapirLevelTwo = true;
    mAlphaSplatMap = nullptr;
    BeHasAlphasplatMap = true;
    BeSaveAlphaSplat = false;
    File_AlphaSplat = "..\\Res\\Terrain\\TerrainAlphaSplat.png";
    File_Effect = "..\\Res\\Terrain\\TerrainEffect.fx";
    File_BrushConfig = "..\\Res\\Terrain\\Brushs\\Brushs.xml";
    TerrainEffect = nullptr;
    EH_Diffuse = nullptr;
    mOriginalIndexBuffer = nullptr;
    mDynamicIndexBuffer = nullptr;
    mIndexBuffer = nullptr;
    mVertexBuffer = nullptr;
    mTexture = nullptr;
    mUsingHeightMap = true;
    mCamera = nullptr;

    TextMgr->addText ( &mTerrainCountString );

    //GxComponentFog TerrainFog = new GxComponentFog();
    //   SetComponent ( TerrainFog );
    //GxComponentColour cc = (GxComponentColour)GetComponent(GxComponentType.COLOUR);
    //cc.UseTextureColor = false;

    //Name = typeof ( GxMap ).ToString();
    //VetexNumber=(2^Level+1)*(2^Level+1);
    //NodeNumber=4^0+4^1+4^2+...+4^(Level-1)=(1-4^Level)/(1-4);

    //UpdateEx += new GameUpdateEventHandler ( updateEx );


    mTexture = TextureMgr->getResource ( "..\\Res\\Box\\001.bmp" );
    dMakeColor ( mMtrl.Diffuse, 255, 255, 255, 255 );


    //LoadHeightMap();

    //LoadAlphaMap();
    //LoadBrushs();
    //LoadEffect();



    //ƽ������
    //SmoothProcess();

    //ComputerNormals();
}

void GTerrain::LoadAlphaMap()
{
    if ( !IsFileExist ( File_AlphaSplat.c_str() ) )
    {
        BeHasAlphasplatMap = false;
        return;
    }
    mAlphaSplatMap = new GBitmap ( File_AlphaSplat );

    if ( mAlphaSplatMap->Width != getLineCount() )
    {
        //CXASSERT ( 0 && "AlphaMap�Ŀ��ȱ�����ڵ�ͼ�ĳߴ��һ." );
    }
}

void GTerrain::updateEx()
{
    mRootNode->reset();
    mRootNode->cull ( mCamera, this );

    if ( mLODMode )
    {
        mRootNode->checkShouldRepair ( this );
        mRootNode->repair();
    }
    mDynamicIndexBuffer->clear();
    mRootNode->addIndexToTerrain ( this, mLODMode );

    mTerrainCountString.Format ( "Terrain_Triangle:%d", mDynamicIndexBuffer->size() / 3 );

    u32* pIB;
    mIndexBuffer->Lock ( 0, 0, ( void** ) &pIB, 0 );
    mDynamicIndexBuffer->copyTo ( pIB );
    mIndexBuffer->Unlock();
}

void GTerrain::LoadBrushs()
{
    //BrushSets = new Dictionary<string, string>();
    //Texts = new Dictionary<string, Texture>();

    //XmlDocument doc = new XmlDocument();
    //doc.Load ( File_BrushConfig );
    //XmlNode root = doc.SelectSingleNode ( "Brushs" );
    //XmlNodeList xnl = root.ChildNodes;
    //foreach ( XmlNode xnf in xnl )
    //{
    //    XmlElement xe = ( XmlElement ) xnf;
    //    string file = xe.GetAttribute ( "File" );
    //    string color = xe.GetAttribute ( "Color" );

    //    BrushSets.Add ( file, color );

    //    string fileEx = file.Insert ( 0, "..\\Res\\Terrain\\Brushs\\" );
    //    Texts.Add ( color, GxTexturePool.GetTexture ( fileEx ) );
    //}
}

void GTerrain::LoadEffect()
{
    //TerrainEffect = GxEffect.GetEffect ( File_Effect );

    //Paras = new Dictionary<string, EffectHandle>();

    //Paras.Add ( "A", EffectHandle.FromString ( "xTexture0" ) );
    //Paras.Add ( "R", EffectHandle.FromString ( "xTexture1" ) );
    //Paras.Add ( "G", EffectHandle.FromString ( "xTexture2" ) );
    //Paras.Add ( "B", EffectHandle.FromString ( "xTexture3" ) );

    //EH_Diffuse = EffectHandle.FromString ( "Diffuse" );

    //foreach ( KeyValuePair<string, EffectHandle> ect in Paras )
    //{
    //    TerrainEffect.SetValue ( ect.Value, Texts[ect.Key] );
    //}
}

bool GTerrain::render()
{
    if ( !__super::render() )
        return false;

    //����ģ�����Ĭ��ʹ�ö�����ɫ������
    D9DEVICE->OpenAllLight ( true );
    D9DEVICE->OpenAlphaBlend ( false );
    D9DEVICE->GetDvc()->SetStreamSource ( 0, mVertexBuffer, 0, sizeof ( EXVertex ) );
    D9DEVICE->GetDvc()->SetFVF ( EXVertex::Format );
    D9DEVICE->GetDvc()->SetTexture ( 0, mTexture->getTexture() );
    D9DEVICE->GetDvc()->SetIndices ( mIndexBuffer );
    D9DEVICE->GetDvc()->SetMaterial ( &GMetrialData::mDefaultWhite );
    D9DEVICE->GetDvc()->DrawIndexedPrimitive ( D3DPT_TRIANGLELIST, 0, 0, mLineCount * mLineCount, 0, mDynamicIndexBuffer->size() / 3 );
    //D9DEVICE->GetDvc()->DrawIndexedPrimitive ( D3DPT_TRIANGLELIST, 0, 0, mLineCount * mLineCount, 0,8 );

    //DVC.RenderState.DiffuseMaterialSource = ColorSource.Material;
    //DVC.Material = Mtrl;
    //DVC.VertexFormat = EXVertex.Format;
    //DVC.VertexDeclaration = EXVertex.Vertex_Declaration;
    //DVC.SetStreamSource ( 0, VBuffer, 0 );
    //TerrainEffect.SetValue ( EH_Diffuse, Mtrl.DiffuseColor );
    //TerrainEffect.SetValue (
    //    EffectHandle.FromString ( "matWorldViewProj" ),
    //    Transform.getTransfrom() * GxDevice.DVC.Transform.View * GxDevice.DVC.Transform.Projection
    //);
    //TerrainEffect.Begin ( FX.None );
    //TerrainEffect.BeginPass ( 0 );
    //RootNode->Render();
    //TerrainEffect.EndPass();
    //TerrainEffect.End();
    return true;
}

void GTerrain::createVertexBuffer()
{
    D9DEVICE->GetDvc()->CreateVertexBuffer (
        ( mLineCount ) * ( mLineCount ) * sizeof ( EXVertex )
        , 0, EXVertex::Format
        , D3DPOOL_MANAGED/*D3DPOOL_MANAGED*/
        , &mVertexBuffer
        , 0
    );

    if ( mVertexBuffer != nullptr )
    {
        EXVertex pos;
        EXVertex* data;
        mVertexBuffer->Lock ( 0, 0, ( void** ) &data, D3DLOCK_DISCARD );

        float fHeight = 0.0f;
        float fX = 0.0f;
        float fZ = 0.0f;
        for ( u32 i = 0; i < getLineCount(); i++ )
        {
            for ( u32 j = 0; j < getLineCount(); j++ )
            {
                fX = ( j - getCellCount() / 2.0f ) * mCellWidth;
                fZ = ( i - getCellCount() / 2.0f ) * mCellWidth;
                if ( mUsingHeightMap )
                {
                    fHeight = mHeightMap->GetHeight ( fX, fZ );
                    //fHeight = 0;
                }
                else
                {
                    fHeight = 0;
                }
                pos.Pos = D3DXVECTOR3 ( fX, fHeight, fZ );

                if ( BeHasAlphasplatMap )
                {
                    //CXColor cl = AlphaSplatMap->GetPixel ( j, QNode::LineCount - i - 1 );
                    //pos.Txt1 = new D3DXVECTOR4 ( cl.R / 255.0f, cl.G / 255.0f, cl.B / 255.0f, cl.A / 255.0f );
                }

                //pos.Color = Color.Red.ToArgb();
                pos.Color = 0XDDDDDDFF;
                pos.Tu = j;
                pos.Tv = getCellCount() - i;

                data[ ( getLineCount() ) * i + j] = pos;
            }
        }
        mVertexBuffer->Unlock();
    }
}

void GTerrain::loadHeightMap()
{
    if ( !IsFileExist ( mFileHeightMap.c_str() ) )
    {
        mUsingHeightMap = false;
        return;
    }
    mHeightMap = new GHeightMap (
        ( float ) ( mCellWidth * ( pow ( 2, mRootLevel ) ) ),
        ( float ) ( mCellWidth * ( pow ( 2, mRootLevel ) ) ),
        mHeightMin, mHeightMax,
        mFileHeightMap );
    mUsingHeightMap = mHeightMap->load();
}

void GTerrain::computerNormals()
{
    //����ÿ����ķ���
    if ( mOriginalIndexBuffer == nullptr )
    {
        mOriginalIndexBuffer = new CXBuffer();
        mOriginalIndexBuffer->setElementByteCount ( sizeof ( int ) );
        mOriginalIndexBuffer->reAllocateByElementCount ( getCellCount() * getCellCount() * 2 * 3 );
        int Stride = getLineCount();
        for ( u32 i = 0; i < getCellCount() / 2; i++ )
        {
            for ( u32 j = 0; j < getCellCount() / 2; j++ )
            {
                u32 BaseIndex = ( i * getCellCount() / 2 + j ) * 24;
                mOriginalIndexBuffer->set ( BaseIndex + 0 , ( i * 2 + 1 ) * Stride + j * 2 + 1		);
                mOriginalIndexBuffer->set ( BaseIndex + 1 , ( i * 2 ) * Stride + j * 2				);
                mOriginalIndexBuffer->set ( BaseIndex + 2 , ( i * 2 + 1 ) * Stride + j * 2			);

                mOriginalIndexBuffer->set ( BaseIndex + 3 , ( i * 2 + 1 ) * Stride + j * 2 + 1		);
                mOriginalIndexBuffer->set ( BaseIndex + 4 , ( i * 2 ) * Stride + j * 2 + 1			);
                mOriginalIndexBuffer->set ( BaseIndex + 5 , ( i * 2 ) * Stride + j * 2				);

                mOriginalIndexBuffer->set ( BaseIndex + 6 , ( i * 2 + 1 ) * Stride + j * 2 + 1		);
                mOriginalIndexBuffer->set ( BaseIndex + 7 , ( i * 2 ) * Stride + ( j + 1 ) * 2		);
                mOriginalIndexBuffer->set ( BaseIndex + 8 , ( i * 2 ) * Stride + j * 2 + 1			);

                mOriginalIndexBuffer->set ( BaseIndex + 9 , ( i * 2 + 1 ) * Stride + j * 2 + 1		);
                mOriginalIndexBuffer->set ( BaseIndex + 10, ( i * 2 + 1 ) * Stride + ( j + 1 ) * 2	);
                mOriginalIndexBuffer->set ( BaseIndex + 11, ( i * 2 ) * Stride + j * 2 + 1			);

                mOriginalIndexBuffer->set ( BaseIndex + 12, ( i * 2 + 1 ) * Stride + j * 2 + 1			);
                mOriginalIndexBuffer->set ( BaseIndex + 13, ( ( i + 1 ) * 2 ) * Stride + ( j + 1 ) * 2	);
                mOriginalIndexBuffer->set ( BaseIndex + 14, ( i * 2 + 1 ) * Stride + ( j + 1 ) * 2		);

                mOriginalIndexBuffer->set ( BaseIndex + 15, ( i * 2 + 1 ) * Stride + j * 2 + 1			);
                mOriginalIndexBuffer->set ( BaseIndex + 16, ( ( i + 1 ) * 2 ) * Stride + j * 2 + 1		);
                mOriginalIndexBuffer->set ( BaseIndex + 17, ( ( i + 1 ) * 2 ) * Stride + ( j + 1 ) * 2	);

                mOriginalIndexBuffer->set ( BaseIndex + 18, ( i * 2 + 1 ) * Stride + j * 2 + 1			);
                mOriginalIndexBuffer->set ( BaseIndex + 19, ( i * 2 + 1 ) * Stride + j * 2				);
                mOriginalIndexBuffer->set ( BaseIndex + 20, ( ( i + 1 ) * 2 ) * Stride + j * 2 + 1		);

                mOriginalIndexBuffer->set ( BaseIndex + 21, ( i * 2 + 1 ) * Stride + j * 2 + 1			);
                mOriginalIndexBuffer->set ( BaseIndex + 22, ( i * 2 + 1 ) * Stride + j * 2				);
                mOriginalIndexBuffer->set ( BaseIndex + 23, ( ( i + 1 ) * 2 ) * Stride + j * 2 + 1		);
            }
        }
    }


    EXVertex* VData;
    mVertexBuffer->Lock ( 0, 0, ( void** ) &VData, D3DLOCK_DISCARD );
    int normalCnt = mOriginalIndexBuffer->capacity() / 3;
    D3DXVECTOR3* Normals = new D3DXVECTOR3[normalCnt];

    D3DXVECTOR3 V[3];

    for ( int i = 0; i < normalCnt; i++ )
    {
        V[0] = VData[mOriginalIndexBuffer->get<u32> ( i * 3 )].Pos;
        V[1] = VData[mOriginalIndexBuffer->get<u32> ( i * 3 + 1 )].Pos;
        V[2] = VData[mOriginalIndexBuffer->get<u32> ( i * 3 + 2 )].Pos;
        dVector3Cross ( Normals[i], V[1] - V[0], V[2] - V[0] );
        dVector3Normalize ( Normals[i] );
    }

    for ( u32 i = 0; i < getCellCount() / 2; i++ )
    {
        for ( u32 j = 0; j < getCellCount() / 2; j++ )
        {
            int VertexBaseIndex = ( i * getCellCount() / 2 + j ) * 24;
            int FaceBaseIndex = ( i * getCellCount() / 2 + j ) * 8;

            VData[mOriginalIndexBuffer->get<u32> ( VertexBaseIndex + 3 * 0 + 0 )].Normal = (
                        Normals[FaceBaseIndex + 0] +
                        Normals[FaceBaseIndex + 1] +
                        Normals[FaceBaseIndex + 2] +
                        Normals[FaceBaseIndex + 3] +
                        Normals[FaceBaseIndex + 4] +
                        Normals[FaceBaseIndex + 5] +
                        Normals[FaceBaseIndex + 6] +
                        Normals[FaceBaseIndex + 7]
                    );
            dVector3Normalize ( VData[mOriginalIndexBuffer->get<u32> ( VertexBaseIndex + 3 * 0 + 0 )].Normal );

            VData[mOriginalIndexBuffer->get<u32> ( VertexBaseIndex + 3 * 0 + 1 )].Normal += dVector3NormalizeSlow ( Normals[FaceBaseIndex + 0] + Normals[FaceBaseIndex + 1] );
            dVector3Normalize ( VData[mOriginalIndexBuffer->get<u32> ( VertexBaseIndex + 3 * 0 + 1 )].Normal );

            VData[mOriginalIndexBuffer->get<u32> ( VertexBaseIndex + 3 * 1 + 1 )].Normal += dVector3NormalizeSlow ( ( Normals[FaceBaseIndex + 1] + Normals[FaceBaseIndex + 2] ) );
            dVector3Normalize ( VData[mOriginalIndexBuffer->get<u32> ( VertexBaseIndex + 3 * 1 + 1 )].Normal );

            VData[mOriginalIndexBuffer->get<u32> ( VertexBaseIndex + 3 * 2 + 1 )].Normal += dVector3NormalizeSlow ( ( Normals[FaceBaseIndex + 3] + Normals[FaceBaseIndex + 2] ) );
            dVector3Normalize ( VData[mOriginalIndexBuffer->get<u32> ( VertexBaseIndex + 3 * 2 + 1 )].Normal );

            VData[mOriginalIndexBuffer->get<u32> ( VertexBaseIndex + 3 * 3 + 1 )].Normal += dVector3NormalizeSlow ( ( Normals[FaceBaseIndex + 3] + Normals[FaceBaseIndex + 4] ) );
            dVector3Normalize ( VData[mOriginalIndexBuffer->get<u32> ( VertexBaseIndex + 3 * 3 + 1 )].Normal );

            VData[mOriginalIndexBuffer->get<u32> ( VertexBaseIndex + 3 * 4 + 1 )].Normal += dVector3NormalizeSlow ( ( Normals[FaceBaseIndex + 5] + Normals[FaceBaseIndex + 4] ) );
            dVector3Normalize ( VData[mOriginalIndexBuffer->get<u32> ( VertexBaseIndex + 3 * 4 + 1 )].Normal );

            VData[mOriginalIndexBuffer->get<u32> ( VertexBaseIndex + 3 * 5 + 1 )].Normal += dVector3NormalizeSlow ( ( Normals[FaceBaseIndex + 5] + Normals[FaceBaseIndex + 6] ) );
            dVector3Normalize ( VData[mOriginalIndexBuffer->get<u32> ( VertexBaseIndex + 3 * 5 + 1 )].Normal );

            VData[mOriginalIndexBuffer->get<u32> ( VertexBaseIndex + 3 * 6 + 1 )].Normal += dVector3NormalizeSlow ( ( Normals[FaceBaseIndex + 7] + Normals[FaceBaseIndex + 6] ) );
            dVector3Normalize ( VData[mOriginalIndexBuffer->get<u32> ( VertexBaseIndex + 3 * 6 + 1 )].Normal );

            VData[mOriginalIndexBuffer->get<u32> ( VertexBaseIndex + 3 * 7 + 1 )].Normal += dVector3NormalizeSlow ( ( Normals[FaceBaseIndex + 7] + Normals[FaceBaseIndex + 0] ) );
            dVector3Normalize ( VData[mOriginalIndexBuffer->get<u32> ( VertexBaseIndex + 3 * 7 + 1 )].Normal );

        }
    }
    dSafeDeleteArray ( Normals );
    dSafeDelete ( mOriginalIndexBuffer );
    mVertexBuffer->Unlock();
}

void GTerrain::smoothProcess()
{
    EXVertex* data;
    mVertexBuffer->Lock ( 0, 0, ( void** ) &data, D3DLOCK_DISCARD );
    for ( u32 i = 1; i < getCellCount(); i++ )
    {
        for ( u32 j = 1; j < getCellCount(); j++ )
        {
            data[i * getLineCount() + j].Pos.y = 1.0f / 9.0f * (
                    data[ ( i + 1 ) * getLineCount() + j - 1].Pos.y +
                    data[ ( i + 1 ) * getLineCount() + j].Pos.y +
                    data[ ( i + 1 ) * getLineCount() + j + 1].Pos.y +

                    data[i * getLineCount() + j - 1].Pos.y +
                    data[i * getLineCount() + j].Pos.y +
                    data[i * getLineCount() + j + 1].Pos.y +

                    data[ ( i - 1 ) * getLineCount() + j - 1].Pos.y +
                    data[ ( i - 1 ) * getLineCount() + j].Pos.y +
                    data[ ( i - 1 ) * getLineCount() + j + 1].Pos.y
                                                 );
        }
    }
    mVertexBuffer->Unlock();
}

void GTerrain::AlterHeight ( HitInfo* HI, EXVertex* MyVB )
{
    if ( HI == nullptr || MyVB == nullptr || !EditHeight )
        return;

    float HeightDelta = 0.01f;

    MyVB[HI->Index[0]].Pos.y += HeightDelta;
    MyVB[HI->Index[1]].Pos.y += HeightDelta;
    MyVB[HI->Index[2]].Pos.y += HeightDelta;

    mHeightMap->SetHeight ( MyVB[HI->Index[0]].Pos.x, MyVB[HI->Index[0]].Pos.z, ( byte ) ( MyVB[HI->Index[0]].Pos.y ) );
    mHeightMap->SetHeight ( MyVB[HI->Index[1]].Pos.x, MyVB[HI->Index[1]].Pos.z, ( byte ) ( MyVB[HI->Index[1]].Pos.y ) );
    mHeightMap->SetHeight ( MyVB[HI->Index[2]].Pos.x, MyVB[HI->Index[2]].Pos.z, ( byte ) ( MyVB[HI->Index[2]].Pos.y ) );
}

void GTerrain::CheckValue ( D3DXVECTOR4& v )
{
    //if (X>1.0f)
    //{
    //    X = 1.0f;
    //}
    float Sum = v.x + v.y + v.z + v.w;
    v.x /= Sum;
    v.y /= Sum;
    v.z /= Sum;
    v.w /= Sum;
}

bool GTerrain::CheckIndexInvalid ( u32 Index )
{
    return Index >= 0 && Index < getLineCount() * getLineCount();
}

void GTerrain::AlterFace ( HitInfo* HI, EXVertex* MyVB )
{
    if ( HI == nullptr || MyVB == nullptr || !EditFace )
        return;
    mAlterFaceIndexListMap.clear();

    mAlterFaceIndexListMap.Insert ( 0, new AlterFaceList );

    for ( int i = 0; i < 3; i++ )
    {
        mAlterFaceIndexListMap[0]->push_back ( HI->Index[i] );
    }
    int tmp = 0;
    for ( int j = 1; j < 2; j++ )
    {
        mAlterFaceIndexListMap.Insert ( j, new AlterFaceList );
        if ( !mAlterFaceIndexListMap.findkey ( j + 1 ) )
        {
            mAlterFaceIndexListMap.Insert ( j + 1, new AlterFaceList );
        }
        for ( int i = 0; i < 3; i++ )
        {
            tmp = HI->Index[i] + 1;
            if ( !mAlterFaceIndexListMap[j - 1]->Find ( tmp ) && !mAlterFaceIndexListMap[j]->Find ( tmp ) )
            {
                mAlterFaceIndexListMap[j]->push_back ( tmp );
            }
        }
        for ( int i = 0; i < 3; i++ )
        {
            tmp = HI->Index[i] - 1;

            if ( !mAlterFaceIndexListMap[j - 1]->Find ( tmp ) && !mAlterFaceIndexListMap[j]->Find ( tmp ) )
            {
                mAlterFaceIndexListMap[j]->push_back ( tmp );
            }
        }
        for ( int i = 0; i < 3; i++ )
        {
            tmp = HI->Index[i] + getLineCount();

            if ( !mAlterFaceIndexListMap[j - 1]->Find ( tmp ) && !mAlterFaceIndexListMap[j]->Find ( tmp ) )
            {
                mAlterFaceIndexListMap[j]->push_back ( tmp );
            }
        }
        for ( int i = 0; i < 3; i++ )
        {
            tmp = HI->Index[i] - getLineCount();

            if ( !mAlterFaceIndexListMap[j - 1]->Find ( tmp ) && !mAlterFaceIndexListMap[j]->Find ( tmp ) )
            {
                mAlterFaceIndexListMap[j]->push_back ( tmp );
            }
        }


        //for (int i = 0; i < 3; i++)
        //{
        //    tmp=HI->Index[i] + QNode::LineCount+1;

        //    if (!IndexList[j].Contains(tmp) && !IndexList[j - 1].Contains(tmp))
        //    {
        //        IndexList[j+1].Add(tmp);
        //    }
        //}
        //for (int i = 0; i < 3; i++)
        //{
        //    tmp=HI->Index[i] + QNode::LineCount-1;

        //    if (!IndexList[j ].Contains(tmp) && !IndexList[j-1].Contains(tmp))
        //    {
        //        IndexList[j + 1].Add(tmp);
        //    }
        //}

        //for (int i = 0; i < 3; i++)
        //{
        //    tmp=HI->Index[i] - QNode::LineCount+1;

        //    if (!IndexList[j].Contains(tmp) && !IndexList[j - 1].Contains(tmp))
        //    {
        //        IndexList[j + 1].Add(tmp);
        //    }
        //}
        //for (int i = 0; i < 3; i++)
        //{
        //    tmp=HI->Index[i] - QNode::LineCount-1;

        //    if (!IndexList[j].Contains(tmp) && !IndexList[j - 1].Contains(tmp))
        //    {
        //        IndexList[j + 1].Add(tmp);
        //    }
        //}
    }

    //float Delta = 0.5f;
    //float factor = 0.5f;
    //for ( int i = 0; i < 3; i++ )
    //{

    //    switch ( GxPlugin_TerrainTool.GetSingleton().CurrentBrush )
    //    {
    //    case "A":
    //        MyVB[HI->Index[i]].Txt1.W += Delta;
    //        break;
    //    case "R":
    //        MyVB[HI->Index[i]].Txt1.X += Delta;
    //        break;
    //    case "G":
    //        MyVB[HI->Index[i]].Txt1.Y += Delta;
    //        break;
    //    case "B":
    //        MyVB[HI->Index[i]].Txt1.Z += Delta;
    //        break;
    //    }
    //    CheckValue ( ref MyVB[HI->Index[i]].Txt1 );


    //}
    //foreach ( KeyValuePair<int, List<int>> il in mAlterFaceIndexListMap )
    //{
    //    foreach ( int inx in il.Value )
    //    {
    //        if ( CheckIndexInvalid ( inx ) )
    //        {
    //            switch ( GxPlugin_TerrainTool.GetSingleton().CurrentBrush )
    //            {
    //            case "R":
    //                MyVB[inx].Txt1.X += ( float ) ( pow ( factor, il.Key ) * Delta );
    //                break;
    //            case "G":
    //                MyVB[inx].Txt1.Y += ( float ) ( pow ( factor, il.Key ) * Delta );
    //                break;
    //            case "B":
    //                MyVB[inx].Txt1.Z += ( float ) ( pow ( factor, il.Key ) * Delta );
    //                break;
    //            case "A":
    //                MyVB[inx].Txt1.W += ( float ) ( pow ( factor, il.Key ) * Delta );
    //                break;
    //            }
    //            CheckValue ( ref MyVB[inx].Txt1 );
    //        }
    //    }
    //}
}

bool GTerrain::Pick ( D3DXVECTOR3 orgin, D3DXVECTOR3 dir )
{
    CXDynaArray<HitInfo*> HIS ;
    mRootNode->pick ( orgin, dir, HIS );

    if ( HIS.size() == 0 )
    {
        return false;
    }
    //HIS.Sort ( HitInfo.SortByDistance );
    HitInfo* HI = HIS[0];
    bool Hited = HI->Hited;
    /*************************************************************************/
    //�޸ĸ߶�
    if ( Hited )
    {

        EXVertex* MyVB;
        mVertexBuffer->Lock ( 0, 0, ( void** ) &MyVB, D3DLOCK_DISCARD );
        AlterHeight ( HI,  MyVB );
        AlterFace ( HI,  MyVB );

        mVertexBuffer->Unlock();
    }

    return Hited;
}

void GTerrain::SaveAlphaSplat()
{
    if ( mAlphaSplatMap == nullptr )
    {
        //AlphaSplatMap = new GBitmap (
        //    QNode::LineCount,
        //    QNode::LineCount,
        //    PixelFormat.Format32bppArgb
        //);
    }


    //EXVertex* VData;
    //mVertexBuffer->Lock ( 0, 0, ( void** ) &VData, D3DLOCK_DISCARD );
    ////������ƽ������
    //for (int i = 1; i < QNode::CellCount; i++)
    //{
    //    for (int j = 1; j < QNode::CellCount; j++)
    //    {
    //        VData[i*QNode::LineCount+j].Txt1=1.0f / 9.0f *
    //            (
    //            VData[(i + 1) * QNode::LineCount + j - 1].Txt1 +
    //            VData[(i + 1) * QNode::LineCount + j].Txt1 +
    //            VData[(i + 1) * QNode::LineCount + j + 1].Txt1 +

    //            VData[i * QNode::LineCount + j - 1].Txt1 +
    //            VData[i * QNode::LineCount + j].Txt1 +
    //            VData[i * QNode::LineCount + j + 1].Txt1 +

    //            VData[(i - 1) * QNode::LineCount + j - 1].Txt1 +
    //            VData[(i - 1) * QNode::LineCount + j].Txt1 +
    //            VData[(i - 1) * QNode::LineCount + j + 1].Txt1
    //            );
    //    }
    //}

    //if ( VData != nullptr )
    //{
    //    D3DXVECTOR4 VTmp = new D3DXVECTOR4 ( 0, 0, 0, 0 );
    //    for ( int i = 0; i < QNode::LineCount; i++ )
    //    {
    //        for ( int j = 0; j < QNode::LineCount; j++ )
    //        {
    //            VTmp = VData[ ( QNode::LineCount - j - 1 ) * QNode::LineCount + i].Txt1;
    //            AlphaSplatMap.SetPixel (
    //                i, j,
    //                Color.FromArgb (
    //                    ( int ) ( VTmp.X * 255.0f ),
    //                    ( int ) ( VTmp.Y * 255.0f ),
    //                    ( int ) ( VTmp.Z * 255.0f ),
    //                    ( int ) ( VTmp.W * 255.0f ) )
    //            );
    //        }
    //    }
    //    string tmpFile = "tmp.png";
    //    AlphaSplatMap.Save ( tmpFile, ImageFormat.Png );
    //    AlphaSplatMap.Dispose();
    //    File.Delete ( File_AlphaSplat );
    //    File.Move ( tmpFile, File_AlphaSplat );
    //    AlphaSplatMap = new GBitmap ( File_AlphaSplat );

    //    mVertexBuffer->Unlock();
    //}
}

GTerrain::~GTerrain()
{
    this->clear();
}

void GTerrain::update()
{
    __super::update();
    mCamera = TheSceneMgr->getCurCamera();
    updateEx();
}

bool GTerrain::isDisplayRepairAreaOnly() const
{
    return mDisplayRepairAreaOnly;
}

u32 GTerrain::getLineCount() const
{
    return mLineCount;
}

u32 GTerrain::getCellCount() const
{
    return mCellCount;
}

void GTerrain::registerAllProperty()
{
    __super::registerAllProperty();
    __RegisterProperty ( mRootLevel );
    __RegisterProperty ( mCellWidth );
    __RegisterProperty ( mLODFactor );
    __RegisterProperty ( mLODMode );
    __RegisterProperty ( mHeightMax );
    __RegisterProperty ( mHeightMin );
}

void GTerrain::setRootLevel ( uchar level )
{
    mRootLevel = level;
}

void GTerrain::setCellWidth ( float width )
{
    mCellWidth = width;
}

bool GTerrain::recreate()
{
    if ( !__super::recreate() )
        return false;

    loadHeightMap();

    if ( !createNodes() )
        return false;

    smoothProcess();

    computerNormals();

    return true;
}

void GTerrain::onPropertyChangeEnd ( void* cur )
{
    if ( cur == &mCellWidth
            || cur == &mRootLevel
            || cur == &mHeightMax
            || cur == &mHeightMin
       )
    {
        recreate();
    }
}
void GTerrain::clear()
{
    dSafeDelete ( mDynamicIndexBuffer );
    dSafeDelete ( mOriginalIndexBuffer );
    dSafeDelete ( mRootNode );

    dSafeDelete ( mAlphaSplatMap );
    dSafeDelete ( mHeightMap );
    dSafeDeleteMap2 ( mNodeMaps );
}

bool GTerrain::createNodes()
{
    mNodeMaps.destroySecond();

    mLineCount = ( int ) pow ( 2, mRootLevel ) + 1;
    mCellCount = mLineCount - 1;

    mDynamicIndexBuffer = new CXBuffer;
    mDynamicIndexBuffer->setElementByteCount ( sizeof ( u32 ) );
    mDynamicIndexBuffer->reAllocateByElementCount ( mCellCount * mCellCount * 2 * 3 * 2 );

    D9DEVICE->GetDvc()->CreateIndexBuffer ( mCellCount * mCellCount * 2 * 3 * 2 * sizeof ( DWORD ), 0, D3DFMT_INDEX32, D3DPOOL_MANAGED, &mIndexBuffer, 0 );
    mRootNode = new GTerrainNode();
    mRootNode->build ( this, mRootLevel );

    createVertexBuffer();
    mRootNode->setVertexBuffer ( mVertexBuffer, this );
    mRootNode->buildNeighbour ( this );

    return true;
}