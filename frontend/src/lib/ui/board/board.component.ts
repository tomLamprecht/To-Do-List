import { Component, Input } from '@angular/core';
import { ListModel } from 'src/lib/data-access/models/listModel';

@Component({
  selector: 'board',
  templateUrl: './board.component.html',
  styleUrls: ['./board.component.scss'],
})
export class BoardComponent {
  @Input()
  title = 'board';

  @Input()
  lists: ListModel[] = [
    {
      id: 0,
      name: 'to do',
      position: 0,
      reminderItems: [
        {
          id: 0,
          title: 'first task',
          position: 0,
          timestamp: '2021-12-09',
          flag: false,
        },
        {
          id: 1,
          title: 'second task',
          position: 1,
          timestamp: '2021-12-09',
          flag: false,
        },
        {
          id: 2,
          title: 'third task',
          position: 2,
          timestamp: '2021-12-09',
          flag: false,
        },
      ],
    },

    {
      id: 1,
      name: 'doing',
      position: 1,
      reminderItems: [
        {
          id: 3,
          title: 'my special first task',
          position: 0,
          timestamp: '2021-12-09',
          flag: false,
        },
      ],
    },
  ];

  @Input()
  displayList:ListModel;

  updateDisplayList(list:ListModel) {
    this.displayList=list;
  }

  changeListTitle(event, list) {
    list.name = event;
  }

}
