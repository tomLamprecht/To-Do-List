import { NgModule } from '@angular/core';
import { BrowserModule } from '@angular/platform-browser';
import { ListDisplayerComponent } from 'src/lib/ui/listDisplayer/listDisplayer.component';
import { ListComponent } from 'src/lib/ui/list/list.component';
import { BoardComponent } from 'src/lib/ui/board/board.component';
import { ReminderItemComponent } from 'src/lib/ui/reminderItem/reminderItem.component';
import { ToolbarComponent } from 'src/lib/ui/toolbar/toolbar.component';
import { AppRoutingModule } from './app-routing.module';
import { AppComponent } from './app.component';
import { ListHeaderComponent } from 'src/lib/ui/listHeader/listHeader.component';
import { ListHeaderContainerComponent } from 'src/lib/ui/listHeaderContainer/listHeaderContainer.component';


@NgModule({
  declarations: [AppComponent, ToolbarComponent, ListDisplayerComponent, ListComponent, ReminderItemComponent, BoardComponent, ListHeaderComponent, ListHeaderContainerComponent],
  imports: [BrowserModule, AppRoutingModule],
  providers: [],
  bootstrap: [AppComponent],
})
export class AppModule {}
