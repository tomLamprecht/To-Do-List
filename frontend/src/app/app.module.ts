import { NgModule } from '@angular/core';
import { BrowserModule } from '@angular/platform-browser';
import { BoardComponent } from 'src/lib/ui/board/board.component';
import { ListComponent } from 'src/lib/ui/list/list.component';
import { ReminderItemComponent } from 'src/lib/ui/reminderItem/reminderItem.component';
import { ToolbarComponent } from 'src/lib/ui/toolbar/toolbar.component';
import { AppRoutingModule } from './app-routing.module';
import { AppComponent } from './app.component';


@NgModule({
  declarations: [AppComponent, ToolbarComponent, BoardComponent, ListComponent, ReminderItemComponent],
  imports: [BrowserModule, AppRoutingModule],
  providers: [],
  bootstrap: [AppComponent],
})
export class AppModule {}
