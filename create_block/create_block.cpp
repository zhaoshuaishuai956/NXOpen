﻿//==============================================================================
//  WARNING!!  This file is overwritten by the Block UI Styler while generating
//  the automation code. Any modifications to this file will be lost after
//  generating the code again.
//
//       Filename:  C:\Users\zhaoshen\Desktop\创建长方体\create_block.cpp
//
//        This file was generated by the NX Block UI Styler
//        Created by: zhaoshen
//              Version: NX 1847
//              Date: 06-20-2025  (Format: mm-dd-yyyy)
//              Time: 16:07 (Format: hh-mm)
//
//==============================================================================

//==============================================================================
//  Purpose:  This TEMPLATE file contains C++ source to guide you in the
//  construction of your Block application dialog. The generation of your
//  dialog file (.dlx extension) is the first step towards dialog construction
//  within NX.  You must now create a NX Open application that
//  utilizes this file (.dlx).
//
//  The information in this file provides you with the following:
//
//  1.  Help on how to load and display your Block UI Styler dialog in NX
//      using APIs provided in NXOpen.BlockStyler namespace
//  2.  The empty callback methods (stubs) associated with your dialog items
//      have also been placed in this file. These empty methods have been
//      created simply to start you along with your coding requirements.
//      The method name, argument list and possible return values have already
//      been provided for you.
//==============================================================================

//------------------------------------------------------------------------------
//These includes are needed for the following template code
//------------------------------------------------------------------------------
#include "create_block.hpp"
#include <uf.h>
#include <uf_modl_primitives.h>
#include <vector>           // 使用 std::vector
#include <exception>        // 使用 std::exception
#include <cstdio>           // 使用 sprintf
#include <NXOpen/BlockStyler_SpecifyPoint.hxx> // SpecifyPoint类

using namespace NXOpen;
using namespace NXOpen::BlockStyler;

//------------------------------------------------------------------------------
// Initialize static variables
//------------------------------------------------------------------------------
Session *(create_block::theSession) = NULL;
UI *(create_block::theUI) = NULL;
//------------------------------------------------------------------------------
// Constructor for NX Styler class
//------------------------------------------------------------------------------
create_block::create_block()
{
    try
    {
        // Initialize the NX Open C++ API environment
        create_block::theSession = NXOpen::Session::GetSession();
        create_block::theUI = UI::GetUI();
        theDlxFileName = "create_block.dlx";
        theDialog = create_block::theUI->CreateDialog(theDlxFileName);
        // Registration of callback functions
        theDialog->AddApplyHandler(make_callback(this, &create_block::apply_cb));
        theDialog->AddOkHandler(make_callback(this, &create_block::ok_cb));
        theDialog->AddUpdateHandler(make_callback(this, &create_block::update_cb));
        theDialog->AddInitializeHandler(make_callback(this, &create_block::initialize_cb));
        theDialog->AddDialogShownHandler(make_callback(this, &create_block::dialogShown_cb));
    }
    catch(exception& ex)
    {
        //---- Enter your exception handling code here -----
        throw;
    }
}

//------------------------------------------------------------------------------
// Destructor for NX Styler class
//------------------------------------------------------------------------------
create_block::~create_block()
{
    if (theDialog != NULL)
    {
        delete theDialog;
        theDialog = NULL;
    }
}
//------------------------------- DIALOG LAUNCHING ---------------------------------
//
//    Before invoking this application one needs to open any part/empty part in NX
//    because of the behavior of the blocks.
//
//    Make sure the dlx file is in one of the following locations:
//        1.) From where NX session is launched
//        2.) $UGII_USER_DIR/application
//        3.) For released applications, using UGII_CUSTOM_DIRECTORY_FILE is highly
//            recommended. This variable is set to a full directory path to a file 
//            containing a list of root directories for all custom applications.
//            e.g., UGII_CUSTOM_DIRECTORY_FILE=$UGII_BASE_DIR\ugii\menus\custom_dirs.dat
//
//    You can create the dialog using one of the following way:
//
//    1. USER EXIT
//
//        1) Create the Shared Library -- Refer "Block UI Styler programmer's guide"
//        2) Invoke the Shared Library through File->Execute->NX Open menu.
//
//------------------------------------------------------------------------------
extern "C" DllExport void  ufusr(char *param, int *retcod, int param_len)
{
    create_block *thecreate_block = NULL;
    try
    {
        thecreate_block = new create_block();
        // The following method shows the dialog immediately
        thecreate_block->Show();
    }
    catch(exception& ex)
    {
        //---- Enter your exception handling code here -----
        create_block::theUI->NXMessageBox()->Show("Block Styler", NXOpen::NXMessageBox::DialogTypeError, ex.what());
    }
    if(thecreate_block != NULL)
    {
        delete thecreate_block;
        thecreate_block = NULL;
    }
}

//------------------------------------------------------------------------------
// This method specifies how a shared image is unloaded from memory
// within NX. This method gives you the capability to unload an
// internal NX Open application or user  exit from NX. Specify any
// one of the three constants as a return value to determine the type
// of unload to perform:
//
//
//    Immediately : unload the library as soon as the automation program has completed
//    Explicitly  : unload the library from the "Unload Shared Image" dialog
//    AtTermination : unload the library when the NX session terminates
//
//
// NOTE:  A program which associates NX Open applications with the menubar
// MUST NOT use this option since it will UNLOAD your NX Open application image
// from the menubar.
//------------------------------------------------------------------------------
extern "C" DllExport int ufusr_ask_unload()
{
    //return (int)Session::LibraryUnloadOptionExplicitly;
    return (int)Session::LibraryUnloadOptionImmediately;
    //return (int)Session::LibraryUnloadOptionAtTermination;
}

//------------------------------------------------------------------------------
// Following method cleanup any housekeeping chores that may be needed.
// This method is automatically called by NX.
//------------------------------------------------------------------------------
extern "C" DllExport void ufusr_cleanup(void)
{
    try
    {
        //---- Enter your callback code here -----
    }
    catch(exception& ex)
    {
        //---- Enter your exception handling code here -----
        create_block::theUI->NXMessageBox()->Show("Block Styler", NXOpen::NXMessageBox::DialogTypeError, ex.what());
    }
}

int create_block::Show()
{
    try
    {
        theDialog->Show();
    }
    catch(exception& ex)
    {
        //---- Enter your exception handling code here -----
        create_block::theUI->NXMessageBox()->Show("Block Styler", NXOpen::NXMessageBox::DialogTypeError, ex.what());
    }
    return 0;
}

//------------------------------------------------------------------------------
//---------------------Block UI Styler Callback Functions--------------------------
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//Callback Name: initialize_cb
//------------------------------------------------------------------------------
void create_block::initialize_cb()
{
    try
    {
        L1 = dynamic_cast<NXOpen::BlockStyler::DoubleBlock*>(theDialog->TopBlock()->FindBlock("L1"));
        L2 = dynamic_cast<NXOpen::BlockStyler::DoubleBlock*>(theDialog->TopBlock()->FindBlock("L2"));
        L3 = dynamic_cast<NXOpen::BlockStyler::DoubleBlock*>(theDialog->TopBlock()->FindBlock("L3"));
        P0 = dynamic_cast<NXOpen::BlockStyler::SpecifyPoint*>(theDialog->TopBlock()->FindBlock("P0"));
        group0 = dynamic_cast<NXOpen::BlockStyler::Group*>(theDialog->TopBlock()->FindBlock("group0"));
    }
    catch(exception& ex)
    {
        //---- Enter your exception handling code here -----
        create_block::theUI->NXMessageBox()->Show("Block Styler", NXOpen::NXMessageBox::DialogTypeError, ex.what());
    }
}

//------------------------------------------------------------------------------
//Callback Name: dialogShown_cb
//This callback is executed just before the dialog launch. Thus any value set 
//here will take precedence and dialog will be launched showing that value. 
//------------------------------------------------------------------------------
void create_block::dialogShown_cb()
{
    try
    {
        //---- Enter your callback code here -----
    }
    catch(exception& ex)
    {
        //---- Enter your exception handling code here -----
        create_block::theUI->NXMessageBox()->Show("Block Styler", NXOpen::NXMessageBox::DialogTypeError, ex.what());
    }
}

//------------------------------------------------------------------------------
//Callback Name: apply_cb
//------------------------------------------------------------------------------
int create_block::apply_cb()
{
    int errorCode = 0;
    try
    {
        // 获取输入值
        double l1Value = L1->Value();
        double l2Value = L2->Value();
        double l3Value = L3->Value();

        // 检查输入是否合法
        if (l1Value <= 0.0 || l2Value <= 0.0 || l3Value <= 0.0)
        {
            create_block::theUI->NXMessageBox()->Show(
                "参数错误",
                NXOpen::NXMessageBox::DialogTypeWarning,
                "长、宽、高必须大于0！"
            );
            return 1; // 返回错误码
        }

        UF_initialize();

        char szLength[MAX_TEXT_LENGTH];
        char szWidth[MAX_TEXT_LENGTH];
        char szHeight[MAX_TEXT_LENGTH];
        sprintf(szLength, "%lf", l1Value);
        sprintf(szWidth, "%lf", l2Value);
        sprintf(szHeight, "%lf", l3Value);
        NXOpen::Point3d p0Value = P0->Point();

        // 计算原点，使其在体中心
        double origin[3] = {
            p0Value.X - l1Value / 2.0,
            p0Value.Y - l2Value / 2.0,
            p0Value.Z - l3Value / 2.0
        };

        char* edge_len[3] = { szLength, szWidth, szHeight };
        tag_t blk_obj_id = NULL_TAG;
        UF_MODL_create_block1(UF_NULLSIGN, origin, edge_len, &blk_obj_id);

        UF_terminate();
    }
    catch(exception& ex)
    {
        errorCode = 1;
        create_block::theUI->NXMessageBox()->Show("Block Styler", NXOpen::NXMessageBox::DialogTypeError, ex.what());
    }
    return errorCode;
}

//------------------------------------------------------------------------------
//Callback Name: update_cb
//------------------------------------------------------------------------------
int create_block::update_cb(NXOpen::BlockStyler::UIBlock* block)
{
    try
    {
        if(block == L1)
        {
        //---------Enter your code here-----------
        }
        else if(block == L2)
        {
        //---------Enter your code here-----------
        }
        else if(block == L3)
        {
        //---------Enter your code here-----------
        }
        else if(block == P0)
        {
        //---------Enter your code here-----------
        }
    }
    catch(exception& ex)
    {
        //---- Enter your exception handling code here -----
        create_block::theUI->NXMessageBox()->Show("Block Styler", NXOpen::NXMessageBox::DialogTypeError, ex.what());
    }
    return 0;
}

//------------------------------------------------------------------------------
//Callback Name: ok_cb
//------------------------------------------------------------------------------
int create_block::ok_cb()
{
    int errorCode = 0; // 定义并初始化错误码为0，表示默认无错误
    try
    {

        errorCode = apply_cb(); // 调用 apply_cb() 方法，执行主要的应用逻辑，并获取其返回的错误码
    }
    catch(exception& ex)
    {
        // 如果 try 块中的代码抛出异常，则进入此 catch 块
        errorCode = 1; // 设置错误码为1，表示发生了错误
        create_block::theUI->NXMessageBox()->Show(
            "Block Styler", 
            NXOpen::NXMessageBox::DialogTypeError, 
            ex.what()
        ); // 弹出错误消息框，显示异常信息
    }
    return errorCode; // 返回错误码，0表示成功，1表示失败
}

//------------------------------------------------------------------------------
//Function Name: GetBlockProperties
//Description: Returns the propertylist of the specified BlockID
//------------------------------------------------------------------------------
PropertyList* create_block::GetBlockProperties(const char *blockID)
{
    return theDialog->GetBlockProperties(blockID);
}
