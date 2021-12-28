import { Component, Input } from '@angular/core';
import { ListModel } from '../../data-access/models/listModel';

@Component({
  selector: 'board',
  templateUrl: './board.component.html',
  styleUrls: ['./board.component.scss'],
})
export class BoardComponent {
  @Input()
  title = 'board title';

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
          timestamp: '2021-12-09T10:04:42.058Z',
          flag: false,
        },
        {
          id: 1,
          title: 'second task',
          position: 1,
          timestamp: '2021-12-09T10:04:42.058Z',
          flag: false,
        },
        {
          id: 2,
          title: 'third task',
          position: 2,
          timestamp: '2021-12-09T10:04:42.058Z',
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
          timestamp: '2021-12-09T10:04:42.058Z',
          flag: false,
        },
      ],
    },

    // {
    //   id: 2,
    //   name: 'done',
    //   position: 2,
    //   reminderItems: [
    //     {
    //       id: 4,
    //       title: 'first task',
    //       position: 0,
    //       timestamp: '2021-12-09T10:04:42.058Z',
    //       flag: false,
    //     },
    //     {
    //       id: 5,
    //       title: 'second task',
    //       position: 1,
    //       timestamp: '2021-12-09T10:04:42.058Z',
    //       flag: false,
    //     },
    //   ],
    // },
  ];

  // addEmptyColumn() {
  //   this.columns.push({
  //     id: (Math.random() * 10000) | 0,
  //     name: 'Empty',
  //     position: 0,
  //     items: [],
  //   });
  // }

  // deleteColumn(column:ColumnModel) {
  //   var index = this.columns.indexOf(column);
  //   this.columns.splice(index, 1);
  // }

  // changeColumnTitle(column, event) {
  //   column.name = event;
  // }

  // ngAfterViewInit() {
  //   var tmp = document.createElement("input");
  //   document.body.appendChild(tmp);
  //   tmp.focus();
  //   document.body.removeChild(tmp);
  // }

}
