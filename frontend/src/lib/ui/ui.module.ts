import { HttpClientModule } from '@angular/common/http';
import { NgModule } from '@angular/core';
import { BrowserModule } from '@angular/platform-browser';
import { BoardComponent } from 'src/lib/ui/board/board.component';
import { ListComponent } from 'src/lib/ui/list/list.component';
import { ListDisplayerComponent } from 'src/lib/ui/listDisplayer/listDisplayer.component';
import { ListHeaderComponent } from 'src/lib/ui/listHeader/listHeader.component';
import { ListHeaderContainerComponent } from 'src/lib/ui/listHeaderContainer/listHeaderContainer.component';
import { ReminderItemComponent } from 'src/lib/ui/reminderItem/reminderItem.component';
import { ToolbarComponent } from 'src/lib/ui/toolbar/toolbar.component';
import { BackendService } from '../feature/backend.service';

@NgModule({
  declarations: [ToolbarComponent, ListDisplayerComponent, ListComponent, ReminderItemComponent, BoardComponent, ListHeaderComponent, ListHeaderContainerComponent],
  imports: [HttpClientModule, BrowserModule],
  providers: [BackendService],
  exports: [ToolbarComponent, BoardComponent]
})
export class UiModule {}
