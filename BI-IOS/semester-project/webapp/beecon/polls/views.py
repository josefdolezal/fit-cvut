from django.shortcuts import render, get_object_or_404
from django.http import HttpResponseRedirect
from django.core.urlresolvers import reverse
from django.views import generic

from .models import Question, Choice

class IndexView( generic.ListView ):
  template_name = 'polls/index.html'
  context_object_name = 'latest_question_list'

  def get_queryset(self):
    """Return the last five published questions."""
    return Question.objects.order_by( '-pub_date' )[:5]


class DetailView( generic.DetailView ):
  model = Question
  template_name = 'polls/detail.html'

class ResultsView( generic.DetailView ):
  model = Question
  template_name = 'polls/results.html'


def vote( request, question_id ):
  question = get_object_or_404( Question, pk=question_id )
  try:
    choice = question.choice_set.get( pk=request.POST['choice'] )
  except ( KeyError, Choice.DoesNotExist ):
    return render( request, 'polls/detail.html', {
      'question': question,
      'error_message': 'You did not select a choice.'
    })
  else:
    choice.votes += 1
    choice.save()
    return HttpResponseRedirect( reverse('polls:results', args=( question_id, ) ) )
