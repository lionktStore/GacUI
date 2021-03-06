#include "GuiScrollControls.h"

namespace vl
{
	namespace presentation
	{
		namespace controls
		{
			using namespace elements;
			using namespace compositions;
			using namespace collections;
			using namespace reflection::description;

/***********************************************************************
GuiScroll::CommandExecutor
***********************************************************************/

			GuiScroll::CommandExecutor::CommandExecutor(GuiScroll* _scroll)
				:scroll(_scroll)
			{
			}

			GuiScroll::CommandExecutor::~CommandExecutor()
			{
			}

			void GuiScroll::CommandExecutor::SmallDecrease()
			{
				scroll->SetPosition(scroll->GetPosition()-scroll->GetSmallMove());
			}

			void GuiScroll::CommandExecutor::SmallIncrease()
			{
				scroll->SetPosition(scroll->GetPosition()+scroll->GetSmallMove());
			}

			void GuiScroll::CommandExecutor::BigDecrease()
			{
				scroll->SetPosition(scroll->GetPosition()-scroll->GetBigMove());
			}

			void GuiScroll::CommandExecutor::BigIncrease()
			{
				scroll->SetPosition(scroll->GetPosition()+scroll->GetBigMove());
			}
			
			void GuiScroll::CommandExecutor::SetTotalSize(vint value)
			{
				scroll->SetTotalSize(value);
			}

			void GuiScroll::CommandExecutor::SetPageSize(vint value)
			{
				scroll->SetPageSize(value);
			}

			void GuiScroll::CommandExecutor::SetPosition(vint value)
			{
				scroll->SetPosition(value);
			}

/***********************************************************************
GuiScroll
***********************************************************************/

			GuiScroll::GuiScroll(IStyleController* _styleController)
				:GuiControl(_styleController)
				,styleController(_styleController)
				,totalSize(100)
				,pageSize(10)
				,position(0)
				,smallMove(1)
				,bigMove(10)
			{
				TotalSizeChanged.SetAssociatedComposition(boundsComposition);
				PageSizeChanged.SetAssociatedComposition(boundsComposition);
				PositionChanged.SetAssociatedComposition(boundsComposition);
				SmallMoveChanged.SetAssociatedComposition(boundsComposition);
				BigMoveChanged.SetAssociatedComposition(boundsComposition);

				commandExecutor=new CommandExecutor(this);
				styleController->SetCommandExecutor(commandExecutor.Obj());
				styleController->SetPageSize(pageSize);
				styleController->SetTotalSize(totalSize);
				styleController->SetPosition(position);
			}

			GuiScroll::~GuiScroll()
			{
			}

			vint GuiScroll::GetTotalSize()
			{
				return totalSize;
			}

			void GuiScroll::SetTotalSize(vint value)
			{
				if(totalSize!=value && 0<value)
				{
					totalSize=value;
					if(pageSize>totalSize)
					{
						SetPageSize(totalSize);
					}
					if(position>GetMaxPosition())
					{
						SetPosition(GetMaxPosition());
					}
					styleController->SetTotalSize(totalSize);
					TotalSizeChanged.Execute(GetNotifyEventArguments());
				}
			}

			vint GuiScroll::GetPageSize()
			{
				return pageSize;
			}

			void GuiScroll::SetPageSize(vint value)
			{
				if(pageSize!=value && 0<=value && value<=totalSize)
				{
					pageSize=value;
					if(position>GetMaxPosition())
					{
						SetPosition(GetMaxPosition());
					}
					styleController->SetPageSize(pageSize);
					PageSizeChanged.Execute(GetNotifyEventArguments());
				}
			}

			vint GuiScroll::GetPosition()
			{
				return position;
			}

			void GuiScroll::SetPosition(vint value)
			{
				vint min=GetMinPosition();
				vint max=GetMaxPosition();
				vint newPosition=
					value<min?min:
					value>max?max:
					value;
				if(position!=newPosition)
				{
					position=newPosition;
					styleController->SetPosition(position);
					PositionChanged.Execute(GetNotifyEventArguments());
				}
			}

			vint GuiScroll::GetSmallMove()
			{
				return smallMove;
			}

			void GuiScroll::SetSmallMove(vint value)
			{
				if(value>0 && smallMove!=value)
				{
					smallMove=value;
					SmallMoveChanged.Execute(GetNotifyEventArguments());
				}
			}

			vint GuiScroll::GetBigMove()
			{
				return bigMove;
			}

			void GuiScroll::SetBigMove(vint value)
			{
				if(value>0 && bigMove!=value)
				{
					bigMove=value;
					BigMoveChanged.Execute(GetNotifyEventArguments());
				}
			}

			vint GuiScroll::GetMinPosition()
			{
				return 0;
			}

			vint GuiScroll::GetMaxPosition()
			{
				return totalSize-pageSize;
			}
		}
	}
}